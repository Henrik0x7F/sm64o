#include "net64/logging.h"

#include "net64/game_messages.h"
#include "net64/util.h"


extern Net64State net64_state_g;

int net64_log(const char* log_message)
{
    const char* msg_ptr = log_message;
    size_t remain_msg_len = strnlen(msg_ptr, 128);
    Net64Message msg;

    if(!net64_is_initialized())
        return 0;

    /* Split log message into as many message packets as necessary */
    while(remain_msg_len > NET64_MSG_DATA_LEN)
    {
        msg.msg_type = NET64_GAME_MSG_LOG_APPEND;
        strncpy((char*)msg.msg_data, msg_ptr, NET64_MSG_DATA_LEN);

        if(!net64_queue_send(&net64_state_g.send_queue, &msg))
            return 0;

        msg_ptr += NET64_MSG_DATA_LEN;
        remain_msg_len = strnlen(msg_ptr, 128);
    }

    msg.msg_type = NET64_GAME_MSG_LOG_END;
    strncpy((char*)msg.msg_data, msg_ptr, NET64_MSG_DATA_LEN);

    return net64_queue_send(&net64_state_g.send_queue, &msg);
}
