#ifndef NET64_NET64_H
#define NET64_NET64_H

#include <ultra64.h>
#include "types.h"
#include "net64/message_queue.h"


/* Magic number indicating to the client that net64 finished initializing */
#define NET64_MAGIC_NUMBER 0x43303050 /* "C00P" */

/* Net64 version info */
#define NET64_VERSION 0
#define NET64_COMPAT_VERSION 0

/* Location of the pointer to net64's global state */
#define NET64_HEADER_PTR_ADDR 0x807FFFFC
/* Location of magic number */
#define NET64_MAGIC_NUMBER_ADDR 0x807FFFF8

/* Message queue sizes */
#define NET64_RCV_MSG_QUEUE_SIZE 64
#define NET64_SND_MSG_QUEUE_SIZE 64

/* Net64 global state */
typedef struct
{
    /* Message queues */
    message_queue_t receive_queue,
                    send_queue;
    queue_descriptor_t receive_queue_descriptors[NET64_RCV_MSG_QUEUE_SIZE],
                       send_queue_descriptors[NET64_SND_MSG_QUEUE_SIZE];
    queue_message_t receive_queue_messages[NET64_RCV_MSG_QUEUE_SIZE],
                    send_queue_messages[NET64_SND_MSG_QUEUE_SIZE];

    /* Pointer to global entity list */
    struct ObjectNode* object_lists;
}net64_state_t;


s32 net64_initialize();

s32 net64_is_initialized();

void net64_tick();

#endif
