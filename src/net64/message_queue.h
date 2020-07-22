#ifndef NET64_MESSAGE_QUEUE_H
#define NET64_MESSAGE_QUEUE_H

#include "string.h"


#define NET64_MSG_DATA_LEN 14

typedef u16 net64_msg_type_t;
typedef u8 net64_queue_size_t;
typedef u8 net64_queue_descriptor_t;

typedef struct
{
    net64_msg_type_t msg_type;
    u8 msg_data[NET64_MSG_DATA_LEN];
}Net64Message;

typedef struct
{
    net64_queue_size_t game_index,
                       client_index,
                       size;
    net64_queue_descriptor_t* descriptor_array;
    Net64Message* message_array;
}Net64Queue;


/* Initialize a message queue.
 * It's the callers responsibility to allocate and free memory.
 */
void net64_queue_create(
    Net64Queue* queue,
    net64_queue_descriptor_t* descriptor_array,
    Net64Message* msg_array,
    net64_queue_size_t queue_size
);

/* Put a message into the message queue.
 * Returns 1 if successfull.
 * 0 if the queue is currently full and the message could not be placed into it.
 */
s32 net64_queue_send(
    Net64Queue* queue,
    Net64Message* msg
);

/* Poll for new messages.
 * Returns 1 if a new message was read from the queue.
 * 0 if the queue is empty and no message was placed in msg.
 */
s32 net64_queue_poll(
    Net64Queue* queue,
    Net64Message* msg
);

#endif
