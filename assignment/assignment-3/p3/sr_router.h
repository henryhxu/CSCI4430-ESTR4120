#ifndef SR_ROUTER_H
#define SR_ROUTER_H

#include "sr_if.h"

#define SR_NUM_INTERFACES 2  

#define INTERFACE0 "veth0"
#define INTERFACE1 "veth1"

/* forward declare */
struct sr_if;
struct sr_arpcache;

// Router
struct sr_instance {
    struct sr_interface ifaces[SR_NUM_INTERFACES];
    struct sr_rt *routing_table;
    struct sr_arpcache *arp_cache;
};
#endif