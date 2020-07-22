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

typedef void(*net64_custom_msg_callback_t)(const u8*, size_t);

typedef struct
{
    u32 remain_ticks;
    char text_buf[13];
}Net64Overlay;

/* Net64 global state */
typedef struct
{
    /* Message queues */
    Net64Queue receive_queue,
               send_queue;
    net64_queue_descriptor_t receive_queue_descriptors[NET64_RCV_MSG_QUEUE_SIZE],
                             send_queue_descriptors[NET64_SND_MSG_QUEUE_SIZE];
    Net64Message receive_queue_messages[NET64_RCV_MSG_QUEUE_SIZE],
                 send_queue_messages[NET64_SND_MSG_QUEUE_SIZE];

    /* Pointer to global entity list */
    struct ObjectNode* object_lists;

    Net64Overlay overlay;
    net64_custom_msg_callback_t custom_msg_callback;
}Net64State;


/* Initialize net64 */
s32 net64_initialize(net64_custom_msg_callback_t msg_callback);

/* Check if net64 is initialized */
s32 net64_is_initialized();

/* Update net64 */
void net64_tick();

/* Send data to server (NET64_MSG_DATA_LEN bytes max) */
s32 net64_send_custom(const u8* data, size_t n);

void net64_set_overlay(u16 duration, const char* text);
void net64_clear_overlay();

#endif
