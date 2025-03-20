#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <netinet/ether.h>

#include "sr_arp.h"
#include "sr_resource.h"

int sr_load_arp(struct sr_instance *sr,const char* filename)
{
    FILE* fp;
    char  line[BUFSIZ];
    char  gw[32];
    char dst_mac[20];

    struct in_addr gw_addr;
    struct ether_addr *dst_mac_addr;

    /* -- REQUIRES -- */
    assert(filename);
    if( access(filename,R_OK) != 0)
    {
        perror("access");
        return -1;
    }

    fp = fopen(filename,"r");

    while( fgets(line,BUFSIZ,fp) != 0)
    {
        sscanf(line,"%s %s",gw,dst_mac);
        if(inet_aton(gw,&gw_addr) == 0)
        { 
            fprintf(stderr,
                    "Error loading routing table, cannot convert %s to valid IP\n",
                    gw);
            return -1; 
        }
        dst_mac_addr = ether_aton(dst_mac);
        if(!dst_mac_addr)
        { 
            fprintf(stderr,
                    "Error loading routing table, cannot convert %s to valid MAC\n",
                    dst_mac);
            return -1; 
        }
        sr_add_arp_entry(sr,gw_addr,dst_mac_addr);
    } /* -- while -- */

    return 0; /* -- success -- */
} /* -- sr_load_arp -- */


void sr_add_arp_entry(struct sr_instance *sr, struct in_addr gw, struct ether_addr *dst_mac_addr)
{
    struct sr_arpcache* arp_walker = 0;

    /* -- REQUIRES -- */
    assert(sr);

    /* -- empty list special case -- */
    if(sr->arp_cache == 0)
    {   
        sr->arp_cache = (struct sr_arpcache*)tracked_malloc(sizeof(struct sr_arpcache));
        assert(sr->arp_cache);
        sr->arp_cache->next = 0;
        sr->arp_cache->ip   = gw;
        memcpy(sr->arp_cache->mac_addr, dst_mac_addr->ether_addr_octet, sizeof(struct ether_addr));

        return;
    }

    /* -- find the end of the list -- */
    arp_walker = sr->arp_cache;
    while(arp_walker->next){
      arp_walker = arp_walker->next; 
    }

    arp_walker->next = (struct sr_arpcache*)tracked_malloc(sizeof(struct sr_arpcache));
    assert(arp_walker->next);
    arp_walker = arp_walker->next;

    arp_walker->next = 0;
    arp_walker->ip   = gw;
    memcpy(arp_walker->mac_addr, dst_mac_addr->ether_addr_octet, sizeof(struct ether_addr));

} /* -- sr_add_arp_entry -- */

void sr_print_arp_cache(struct sr_instance *sr)
{
    struct sr_arpcache* arp_walker = 0;

    if(sr->arp_cache == 0)
    {
        printf(" *warning* ARP cache empty \n");
        return;
    }

    printf("Destination\tARP\t\n");

    arp_walker = sr->arp_cache;
    
    sr_print_arp_entry(arp_walker);
    while(arp_walker->next)
    {
        arp_walker = arp_walker->next; 
        sr_print_arp_entry(arp_walker);
    }

} /* -- sr_print_arp_cache -- */


void sr_print_arp_entry(struct sr_arpcache* entry)
{
    /* -- REQUIRES --*/
    assert(entry);
    printf("%s\t",inet_ntoa(entry->ip));
    printf("%s\t\n",ether_ntoa((struct ether_addr *)entry->mac_addr));

} /* -- sr_print_routing_entry -- */


