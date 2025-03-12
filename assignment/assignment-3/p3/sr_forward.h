#ifndef SR_TODO_H
#define SR_TODO_H

#include <stdint.h>
#include "./sr.h"

void get_src_mac_by_iface(struct sr_instance *sr, const char* iface, uint8_t* mac);
const char* sr_handlepacket(struct sr_instance *sr, uint8_t* packet, int len, const char* recv_iface);
uint16_t debug_print_packet(uint8_t* buf, int len, const char* iface);

#endif