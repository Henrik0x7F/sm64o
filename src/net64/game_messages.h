#ifndef NET64_GAME_MESSAGES_H
#define NET64_GAME_MESSAGES_H

#include <ultra64.h>


enum
{
    GAME_MSG_RESERVED = 0,
    GAME_MSG_LOG_APPEND,   /* Append text to next log message */
    GAME_MSG_LOG_END,      /* Append text to log message and print it */

    GAME_MSG_NUM
};

#endif
