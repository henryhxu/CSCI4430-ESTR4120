#ifndef SR_IF_H
#define SR_IF_H

#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/if_arp.h>
#include <arpa/inet.h>

// Interface structure definition
struct sr_interface {
    char name[IF_NAMESIZE]; 
    int sockfd;
    int ifindex;
    uint8_t mac_addr[ETH_ALEN];  // port MAC address
};

#endif