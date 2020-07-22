#include "net64/net64.h"

#include "net64/util.h"
#include "net64/logging.h"
#include "net64/game_messages.h"
#include "net64/client_messages.h"
#include "game/print.h"
#include "string.h"


extern struct ObjectNode gObjectListArray[16];


/* Tells if net64 has been initialized */
static s32 net64_initialized_l = 0;

/* Show debug information */
s32 net64_show_debug_g = 1;


/* Net64 Header */
typedef struct
{
    u16 compat_version;
    u16 version;
    Net64Queue* receive_queue,
              * send_queue;
    struct ObjectNode* object_lists;
}Net64Header;

static Net64Header net64_header_l;

#define NET64_HEADER_PTR (*((Net64Header**)NET64_HEADER_PTR_ADDR))

/* Global state */
Net64State net64_state_g;


static void write_magic_num();
static void handle_client_msg(Net64Message* msg);

s32 net64_initialize(net64_custom_msg_callback_t msg_callback)
{
    memset(&net64_state_g, 0, sizeof(net64_state_g));

    /* Point header pointer to header */
    NET64_HEADER_PTR = &net64_header_l;

    /* Net64 version info */
    net64_header_l.compat_version = NET64_COMPAT_VERSION;
    net64_header_l.version = NET64_VERSION;


    /* Init message queues */
    net64_queue_create(&net64_state_g.receive_queue, net64_state_g.receive_queue_descriptors,
                       net64_state_g.receive_queue_messages, NET64_RCV_MSG_QUEUE_SIZE);

    net64_queue_create(&net64_state_g.send_queue, net64_state_g.send_queue_descriptors,
                       net64_state_g.send_queue_messages, NET64_SND_MSG_QUEUE_SIZE);

    net64_header_l.receive_queue = &net64_state_g.receive_queue;
    net64_header_l.send_queue = &net64_state_g.send_queue;


    /* Load pointer to object list array */
    net64_state_g.object_lists = gObjectListArray;
    net64_state_g.object_lists = gObjectListArray;

    /* Init custom message callback */
    net64_state_g.custom_msg_callback = msg_callback;

    /* We're done */
    net64_initialized_l = 1;
    write_magic_num();

    return 1;
}

s32 net64_is_initialized()
{
    return net64_initialized_l;
}

static void print_addr(int x, int y, const void* ptr)
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
    Net64Message msg;

    /* Poll for incoming messages */
    if(net64_queue_poll(&net64_state_g.receive_queue, &msg))
    {
        handle_client_msg(&msg);
    }


    if(net64_show_debug_g)
    {
        /* Print debug information about the queue states to the screen */
        print_text_fmt_int(10, 120, "client %d", net64_state_g.receive_queue.client_index);
        print_text_fmt_int(10, 100, "game   %d", net64_state_g.receive_queue.game_index);
        print_text_fmt_int(120, 120, "client %d", net64_state_g.send_queue.client_index);
        print_text_fmt_int(120, 100, "game   %d", net64_state_g.send_queue.game_index);
    }

    /* Update overlay */
    if(net64_state_g.overlay.remain_ticks > 0)
    {
        --net64_state_g.overlay.remain_ticks;
        print_text(10, 10, net64_state_g.overlay.text_buf);
    }
}

s32 net64_send_custom(const u8* data, size_t n)
{
    Net64Message msg;

    if(!net64_is_initialized())
        return 0;

    if(n > NET64_MSG_DATA_LEN)
        return 0;

    msg.msg_type = NET64_GAME_MSG_CUSTOM;
    memcpy(msg.msg_data, data, n);

    return net64_queue_send(&net64_state_g.send_queue, &msg);
}

void net64_set_overlay(u16 duration, const char* text)
{
    net64_state_g.overlay.remain_ticks = duration;
    strncpy(net64_state_g.overlay.text_buf, text, sizeof(net64_state_g.overlay.text_buf));
}

void net64_clear_overlay()
{
    net64_state_g.overlay.remain_ticks = 0;
}

static void write_magic_num()
{
    *((u32*)NET64_MAGIC_NUMBER_ADDR) = NET64_MAGIC_NUMBER;
}

static void on_print_overlay(Net64Message* msg)
{
    u16 ticks;
    memcpy(&ticks, msg->msg_data, sizeof(ticks));
    net64_set_overlay(ticks, (char*)&msg->msg_data[2]);
}

static void handle_client_msg(Net64Message* msg)
{
    switch(msg->msg_type)
    {
        case NET64_CLIENT_MSG_CUSTOM:
            if(net64_state_g.custom_msg_callback)
                custom_msg_callback(msg->msg_data, NET64_MSG_DATA_LEN);
            break;
        case NET64_CLIENT_MSG_PRINT:
            on_print_overlay(msg);
            break;
    }
}
