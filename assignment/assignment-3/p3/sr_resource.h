#ifndef SR_RESOURCE_H
#define SR_RESOURCE_H

struct ResourceNode {
    void* ptr;
    struct ResourceNode* next;
};

void* tracked_malloc(size_t size);
void sr_cleanup_resources();

#endif