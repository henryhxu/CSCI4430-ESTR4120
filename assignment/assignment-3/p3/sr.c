#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <sched.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include "./sr_protocol.h"
#include "./sr.h"
#include "./sr_rt.h"
#include "./sr_router.h"
#include "./sr_arp.h"
#include "./sr_resource.h"
#include "./sr_forward.h"
#include <signal.h>
#include <stdatomic.h>


static atomic_int g_exit_flag = 0;


void sig_handler(int signum) {
    atomic_store(&g_exit_flag, 1);
  
    const char msg[] = "\nTerminating & cleaning\n";
    write(STDERR_FILENO, msg, sizeof(msg)-1);
}

void setup_signal_handlers() {
    struct sigaction sa = {
        .sa_handler = sig_handler,
        .sa_flags = SA_RESTART  
    };
    sigemptyset(&sa.sa_mask);
  
    sigaction(SIGINT, &sa, NULL);   
    sigaction(SIGTERM, &sa, NULL); 
}


// Initialize router interfaces
void sr_init_interfaces(struct sr_instance *sr) {
    strcpy(sr->ifaces[0].name, INTERFACE0);
    sr->ifaces[0].sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    sr->ifaces[0].ifindex = if_nametoindex(INTERFACE0);

    strcpy(sr->ifaces[1].name, INTERFACE1);
    sr->ifaces[1].sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    sr->ifaces[1].ifindex = if_nametoindex(INTERFACE1);

    // Get MAC address
    for(int i=0; i<SR_NUM_INTERFACES; i++) {
        struct ifreq ifr;
        memset(&ifr, 0, sizeof(ifr));
        strncpy(ifr.ifr_name, sr->ifaces[i].name, IF_NAMESIZE);
      
        if(ioctl(sr->ifaces[i].sockfd, SIOCGIFHWADDR, &ifr) < 0) {
            perror("Get MAC failed");
            exit(1);
        }
        memcpy(sr->ifaces[i].mac_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
    }
  
    // Error check
    for(int i=0; i<SR_NUM_INTERFACES; i++) {
        if(sr->ifaces[i].sockfd == -1 || sr->ifaces[i].ifindex == 0) {
            perror("Interface initialization failed");
            exit(1);
        }

        struct sockaddr_ll sll = {
            .sll_family = AF_PACKET,
            .sll_protocol = htons(ETH_P_ALL),
            .sll_ifindex = sr->ifaces[i].ifindex
        };

        if (bind(sr->ifaces[i].sockfd, (struct sockaddr*)&sll, sizeof(sll)) == -1) {
            perror("Bind failed");
            close(sr->ifaces[i].sockfd);
            exit(1);
        }

        printf("Successfully bind to veth%d (ifindex=%d)\n", i, sr->ifaces[i].ifindex);
    }
}




void loop(struct sr_instance *sr) {
    // create epoll instance to monitor multiple interfaces
    int epoll_fd = epoll_create1(0);
    struct epoll_event ev;
  
    for(int i=0; i<SR_NUM_INTERFACES; i++) {
        ev.events = EPOLLIN;
        ev.data.fd = sr->ifaces[i].sockfd;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sr->ifaces[i].sockfd, &ev);
    }

    while (!atomic_load(&g_exit_flag)) {
        struct epoll_event events[2];
        int n = epoll_wait(epoll_fd, events, 2, -1);
      
        for(int i=0; i<n; i++) {
            uint8_t buf[IP_MAXPACKET];
            ssize_t len = recv(events[i].data.fd, buf, sizeof(buf), 0);
          
            if(len > 0) {
                const char* ifname = NULL;
                for(int j=0; j<2; j++) {
                    if(events[i].data.fd == sr->ifaces[j].sockfd) {
                        ifname = sr->ifaces[j].name;
                        break;
                    }
                }
              
                struct sr_ethernet_hdr* eth_hdr = (struct sr_ethernet_hdr*)buf;
                
                const char* target_iface = NULL;
                if (ntohs(eth_hdr->ether_type) != ethertype_arp && ntohs(eth_hdr->ether_type) != 0x86dd){
                    debug_print_packet(buf, len, ifname);
                    target_iface = sr_handlepacket(sr, buf, len, ifname);
                }
                struct sr_interface* target = NULL;

                for(int i=0; i<SR_NUM_INTERFACES; i++) {
                    if(strcmp(sr->ifaces[i].name, target_iface) == 0) {
                        target = &sr->ifaces[i];
                        break;
                    }
                }
    
                struct sockaddr_ll dest_addr = {
                    .sll_family = AF_PACKET,
                    .sll_ifindex = target->ifindex,
                    .sll_halen = ETH_ALEN,
                };
  
                // send packet
                sendto(target->sockfd, buf, len, 0,
                    (struct sockaddr*)&dest_addr, sizeof(dest_addr));
            }
        }
    }

    if (epoll_fd != -1) {
        close(epoll_fd);
        epoll_fd = -1;
        printf("Closed epoll instance\n");
    }

    for (int i = 0; i<SR_NUM_INTERFACES; i++) {
        if (sr->ifaces[i].sockfd != -1) {
            close(sr->ifaces[i].sockfd);
            sr->ifaces[i].sockfd = -1;
            printf("Closed socket for %s\n", sr->ifaces[i].name);
        }
    }

    return;
}

int main() {
    struct sr_instance sr;
    const char *rtable_filename = "rtable";
    const char *arpcache_filename = "arp_cache";
    int ret;

    setup_signal_handlers();

    /* bind interfaces */
    sr_init_interfaces(&sr);

    /* load routing table */
    sr.routing_table = 0;
    ret = sr_load_rt(&sr, rtable_filename);
    if (ret != 0) {
        perror("Routing table loading failed");
        goto cleanup;
    } 
    sr_print_routing_table(&sr);

    /* load ARP cache */
    sr.arp_cache = 0;
    ret = sr_load_arp(&sr, arpcache_filename);
    if (ret != 0) {
        perror("ARP cache loading failed");
        goto cleanup;
    } 
    sr_print_arp_cache(&sr);

    /* start packet processing loop */
    printf("Starting packet processing loop...\n");

    loop(&sr);

cleanup:
    sr_cleanup_resources();
    printf("Resources of SR release, exiting...\n");

    return 0;
}