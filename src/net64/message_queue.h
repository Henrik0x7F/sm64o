#ifndef NET64_MESSAGE_QUEUE_H
#define NET64_MESSAGE_QUEUE_H

#include "string.h"


#define QUEUE_MSG_DATA_LEN 14

typedef u16 queue_msg_type_t;
typedef u8 queue_size_t;
typedef u8 queue_descriptor_t;

typedef struct
{
    queue_msg_type_t msg_type;
    u8 msg_data[QUEUE_MSG_DATA_LEN];
}queue_message_t;

typedef struct
{
    queue_size_t game_index,
                 client_index,
                 size;
    queue_descriptor_t* descriptor_array;
    queue_message_t* message_array;
}message_queue_t;


/* Initialize a message queue.
 * It's the callers responsibility to allocate and free memory.
 */
void create_message_queue(
    message_queue_t* queue,
    queue_descriptor_t* descriptor_array,
    queue_message_t* msg_array,
    queue_size_t queue_size
);

/* Put a message into the message queue.
 * Returns 1 if successfull.
 * 0 if the queue is currently full and the message could not be placed into it.
 */
s32 send_message(
    message_queue_t* queue,
    queue_message_t* msg
);

/* Poll for new messages.
 * Returns 1 if a new message was read from the queue.
 * 0 if the queue is empty and no message was placed in msg.
 */
s32 poll_message(
    message_queue_t* queue,
    queue_message_t* msg
);

#endif
