
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "./sr.h"
#include "./sr_protocol.h"
#include "./sr_if.h"
# include "./sr_rt.h"
#include "sr_forward.h"

// 
static const uint8_t PEER0_MAC[ETH_ALEN] = {0xaa,0xbb,0xcc,0xdd,0xee,0x00};
static const uint8_t PEER1_MAC[ETH_ALEN] = {0xaa,0xbb,0xcc,0xdd,0xee,0x11};

void get_src_mac_by_iface(struct sr_instance *sr, const char* target_iface, uint8_t* mac) {
    struct sr_interface* target = NULL;

    for(int i=0; i<2; i++) {
        if(strcmp(sr->ifaces[i].name, target_iface) == 0) {
            target = &sr->ifaces[i];
            break;
        }
    }

    mac = target->mac_addr;
}


// Packet debugging function
uint16_t debug_print_packet(uint8_t* buf, int len, const char* iface) {
    struct sr_ethernet_hdr* eth_hdr = (struct sr_ethernet_hdr*)buf;

    // Print basic packet info
    printf("\n=== Received %d byte packet @ %s ===\n", len, iface);

    // Parse Ethernet header
    printf("[L2] SRC MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", 
           eth_hdr->ether_shost[0], eth_hdr->ether_shost[1],
           eth_hdr->ether_shost[2], eth_hdr->ether_shost[3],
           eth_hdr->ether_shost[4], eth_hdr->ether_shost[5]);
    printf("    DST MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           eth_hdr->ether_dhost[0], eth_hdr->ether_dhost[1],
           eth_hdr->ether_dhost[2], eth_hdr->ether_dhost[3],
           eth_hdr->ether_dhost[4], eth_hdr->ether_dhost[5]);
    printf("    EtherType: 0x%04x\n", ntohs(eth_hdr->ether_type));

    // Protocol-specific parsing
    if (ntohs(eth_hdr->ether_type) == ethertype_ip) {
        struct sr_ip_hdr* ip_hdr = (struct sr_ip_hdr*)(buf + sizeof(struct sr_ethernet_hdr));
        printf("[L3] IPv4 Version: %d  Header Len: %d bytes\n", 
               ip_hdr->ip_v, ip_hdr->ip_hl * 4);
        printf("     SRC IP: %s\n", inet_ntoa(*(struct in_addr*)&ip_hdr->ip_src));
        printf("     DST IP: %s\n", inet_ntoa(*(struct in_addr*)&ip_hdr->ip_dst));
        printf("     TTL: %d  Protocol: %d\n", ip_hdr->ip_ttl, ip_hdr->ip_p);
    
        if (ip_hdr->ip_p == IPPROTO_ICMP) {
            struct sr_icmp_hdr* icmp_hdr = (struct sr_icmp_hdr*)(ip_hdr + 1);
            printf("[L4] ICMP Type: %d  Code: %d\n",
                   icmp_hdr->icmp_type, icmp_hdr->icmp_code);
        }
    } 
    else if (ntohs(eth_hdr->ether_type) == ethertype_arp) {
        struct sr_arp_hdr* arp_hdr = (struct sr_arp_hdr*)(buf + sizeof(struct sr_ethernet_hdr));
        printf("[ARP] Operation: %s\n", 
               ntohs(arp_hdr->ar_op) == ARPOP_REQUEST ? "Request" : "Reply");
        printf("      Sender IP: %s\n", inet_ntoa(*(struct in_addr*)&arp_hdr->ar_sip));
        printf("      Target IP: %s\n", inet_ntoa(*(struct in_addr*)&arp_hdr->ar_tip));
    }

    printf("--------------------------------\n");
    return eth_hdr->ether_type;
}

// struct sr_rt *result sr_rt_lookup(struct sr_instance *sr)
// {
//     struct sr_rt* rt_walker = 0;

//     if(sr->routing_table == 0)
//     {
//         return rt_walker;
//     }

//     rt_walker = sr->routing_table;

//     while(rt_walker->next)
//     {   
//         if (rt_walker->dest == dest)
//         {
//             return rt_walker;
//         }
//         rt_walker = rt_walker->next; 
//     }
// } /* -- sr_print_routing_table -- */

// Packet handling function
const char* sr_handlepacket(struct sr_instance *sr , uint8_t* packet, int len, const char* recv_iface) {
    
    const char* target_iface = NULL;
    uint8_t src_mac[ETH_ALEN]; 
    uint8_t* dst_mac;

    /* pkt parsing */
    struct sr_ethernet_hdr* eth_hdr = (struct sr_ethernet_hdr*)packet;
    // struct sr_ip_hdr* ip_hdr = (struct sr_ip_hdr*)(buf + sizeof(struct sr_ethernet_hdr));

    // char *dst_ip = inet_ntoa(*(struct in_addr*)&ip_hdr->ip_dst);

    /* check checksum */
    // TODO

    /* routing table lookup */
    if(strcmp(recv_iface, "veth0") == 0) {
        target_iface = "veth1"; // veth0 -> veth1
        get_src_mac_by_iface(sr, "veth0", src_mac);
        dst_mac = PEER1_MAC;
    } 
    else if(strcmp(recv_iface, "veth1") == 0) {
        target_iface = "veth0"; // veth1 -> veth0
        get_src_mac_by_iface(sr, "veth1", src_mac);
        dst_mac = PEER0_MAC;
    } 
    else {
        return NULL;
    }

    /* ARP cache lookup */

    /* packet modification  */
    // struct sr_ethernet_hdr* eth_hdr = (struct sr_ethernet_hdr*)packet;
    // memcpy(dest_addr.sll_addr, eth_hdr->ether_dhost, ETH_ALEN);
    memcpy(eth_hdr->ether_shost, src_mac, ETH_ALEN);
    memcpy(eth_hdr->ether_dhost, dst_mac, ETH_ALEN);

    /* TTL */

    /* checksum */


    return target_iface;

}