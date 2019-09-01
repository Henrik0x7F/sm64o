#include "net64/logging.h"

#include "net64/game_messages.h"
#include "net64/util.h"


extern net64_state_t net64_state_g;

int net64_log(const char* log_message)
{
    const char* msg_ptr = log_message;
    size_t remain_msg_len = strnlen(msg_ptr, 128);
    queue_message_t msg;

    if(!net64_is_initialized())
        return 0;

    /* Split log message into as many message packets as necessary */
    while(remain_msg_len > QUEUE_MSG_DATA_LEN)
    {
        msg.msg_type = GAME_MSG_LOG_APPEND;
        strncpy((char*)msg.msg_data, msg_ptr, QUEUE_MSG_DATA_LEN);

        if(!send_message(&net64_state_g.send_queue, &msg))
            return 0;

        msg_ptr += QUEUE_MSG_DATA_LEN;
        remain_msg_len = strnlen(msg_ptr, 128);
    }

    msg.msg_type = GAME_MSG_LOG_END;
    strncpy((char*)msg.msg_data, msg_ptr, QUEUE_MSG_DATA_LEN);

    return send_message(&net64_state_g.send_queue, &msg);
}
