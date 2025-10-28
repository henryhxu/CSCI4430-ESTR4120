#ifndef SR_ARP_H
#define SR_ARP_H

#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include "./sr_router.h"


// ARP cache
struct sr_arpcache {
    uint8_t mac_addr[ETH_ALEN]; 
    struct in_addr ip;                /* IP addr in network byte order */
    struct sr_arpcache *next;
};

/* Checks if an IP->MAC mapping is in the cache. IP is in network byte order. */
int sr_load_arp(struct sr_instance*,const char*);
void sr_add_arp_entry(struct sr_instance *sr, struct in_addr gw, struct ether_addr *dst_mac_addr);
void sr_print_arp_cache(struct sr_instance*);
void sr_print_arp_entry(struct sr_arpcache*);

#endif