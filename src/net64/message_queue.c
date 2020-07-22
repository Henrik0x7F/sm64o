#include "message_queue.h"

#include "net64/util.h"


enum SlotState
{
    FREE = 0,
    USED
};

void net64_queue_create(
    Net64Queue* queue,
    net64_queue_descriptor_t* descriptor_array,
    Net64Message* msg_array,
    net64_queue_size_t queue_size
)
{
    /* Clean descriptor array */
    memset(descriptor_array, 0, sizeof(net64_queue_descriptor_t) * queue_size);

    /* Init indices */
    queue->game_index = 0;
    queue->client_index = 0;
     /* Set queue size */
    queue->size = queue_size;
    /* Set array pointers */
    queue->descriptor_array = descriptor_array;
    queue->message_array = msg_array;
}

s32 net64_queue_send(
    Net64Queue* queue,
    Net64Message* msg
)
{
    /* If next possibly free slot is still in use the queue is currently full */
    if(queue->descriptor_array[queue->game_index] != FREE)
    {
        return 0;
    }

    /* Write message into free slot */
    memcpy(queue->message_array + queue->game_index, msg, sizeof(*msg));

    /* Mark slot as in use */
    queue->descriptor_array[queue->game_index] = USED;

    /* Increment index */
    if(++queue->game_index == queue->size)
    {
        /* Loop back to front */
        queue->game_index = 0;
    }

    /* Success */
    return 1;
}

s32 net64_queue_poll(
    Net64Queue* queue,
    Net64Message* msg
)
{
    /* If the next possibly used slot is empty the queue is currently empty */
    if(queue->descriptor_array[queue->game_index] != USED)
    {
        return 0;
    }

    /* Read message from the current slot */
    memcpy(msg, queue->message_array + queue->game_index, sizeof(*msg));

    /* Mark slot as free */
    queue->descriptor_array[queue->game_index] = FREE;

    /* Increment index */
    if(++queue->game_index == queue->size)
    {
        /* Loop back to front */
        queue->game_index = 0;
    }

    /* Success */
    return 1;
}
