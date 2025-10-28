#include <stdlib.h>
#include "sr_resource.h"

static struct ResourceNode* g_resource_list = NULL;

void* tracked_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) return NULL;
  
    struct ResourceNode* node = malloc(sizeof(struct ResourceNode));
    node->ptr = ptr;
    node->next = g_resource_list;
    g_resource_list = node;
  
    return ptr;
}

void sr_cleanup_resources() {
    struct ResourceNode* current = g_resource_list;
    while (current) {
        free(current->ptr);
        struct ResourceNode* next = current->next;
        free(current);
        current = next;
    }
    g_resource_list = NULL;
}
