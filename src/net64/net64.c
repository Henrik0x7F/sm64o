#include "net64/net64.h"

#include "net64/util.h"
#include "net64/logging.h"
#include "game/print.h"


extern struct ObjectNode gObjectListArray[16];


/* Tells if net64 has been initialized */
static s32 net64_initialized_g = 0;

/* Show debug information */
static s32 net64_show_debug_g = 1;


/* Net64 Header */
typedef struct
{
    u16 compat_version;
    u16 version;
    message_queue_t* receive_queue,
                   * send_queue;
    struct ObjectNode* object_lists;
}net64_header_t;
static net64_header_t net64_header_g;

#define NET64_HEADER_PTR (*((net64_header_t**)NET64_HEADER_PTR_ADDR))

/* Global state */
net64_state_t net64_state_g;


void write_magic_num();

s32 net64_initialize()
{
    /* Point header pointer to header */
    NET64_HEADER_PTR = &net64_header_g;

    /* Net64 version info */
    net64_header_g.compat_version = NET64_COMPAT_VERSION;
    net64_header_g.version = NET64_VERSION;


    /* Init message queues */
    create_message_queue(&net64_state_g.receive_queue, net64_state_g.receive_queue_descriptors,
                         net64_state_g.receive_queue_messages, NET64_RCV_MSG_QUEUE_SIZE);

    create_message_queue(&net64_state_g.send_queue, net64_state_g.send_queue_descriptors,
                         net64_state_g.send_queue_messages, NET64_SND_MSG_QUEUE_SIZE);

    net64_header_g.receive_queue = &net64_state_g.receive_queue;
    net64_header_g.send_queue = &net64_state_g.send_queue;


    /* Load pointer to object list array */
    net64_state_g.object_lists = gObjectListArray;
    net64_state_g.object_lists = gObjectListArray;

    /* We're done */
    net64_initialized_g = 1;
    write_magic_num();

    return 1;
}

s32 net64_is_initialized()
{
    return net64_initialized_g;
}

void print_addr(int x, int y, const void* ptr)
{
    u32 addr = (u32)ptr;

    u8 b0 = (addr & 0xFF000000) >> 24;
    u8 b1 = (addr & 0xFF0000) >> 16;
    u8 b2 = (addr & 0xFF00) >> 8;
    u8 b3 = (addr & 0xFF);

    print_text_fmt_int(x, y, "%x", b0);
    print_text_fmt_int(x + 30, y, "%x", b1);
    print_text_fmt_int(x + 60, y, "%x", b2);
    print_text_fmt_int(x + 90, y, "%x", b3);
}

void net64_tick()
{
    queue_message_t msg;

    /* Poll for incoming messages */
    if(poll_message(&net64_state_g.receive_queue, &msg))
    {

    }

    print_text_fmt_int(10, 100, "addr %d", *((u32*)NET64_MAGIC_NUMBER_ADDR));

    /* Print debug information about the queue states to the screen */
    print_text_fmt_int(10, 30, "client %d", net64_state_g.receive_queue.client_index);
    print_text_fmt_int(10, 10, "game   %d", net64_state_g.receive_queue.game_index);
    print_text_fmt_int(120, 30, "client %d", net64_state_g.send_queue.client_index);
    print_text_fmt_int(120, 10, "game   %d", net64_state_g.send_queue.game_index);
}

void write_magic_num()
{
    *((u32*)NET64_MAGIC_NUMBER_ADDR) = NET64_MAGIC_NUMBER;
}
