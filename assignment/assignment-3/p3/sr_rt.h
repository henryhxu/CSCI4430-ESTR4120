#ifndef sr_RT_H
#define sr_RT_H

#include <netinet/in.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include "./sr_router.h"

// Routing table
struct sr_rt
{
    struct in_addr dest;
    struct in_addr gw;
    struct in_addr mask;
    char interface[IF_NAMESIZE];
    struct sr_rt* next;
};


int sr_load_rt(struct sr_instance *,const char*);
void sr_add_rt_entry(struct sr_instance *sr, struct in_addr,struct in_addr,
                  struct in_addr, char*);
void sr_print_routing_table(struct sr_instance *);
void sr_print_routing_entry(struct sr_rt*);


#endif  /* --  sr_RT_H -- */