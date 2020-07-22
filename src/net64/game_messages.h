#ifndef NET64_GAME_MESSAGES_H
#define NET64_GAME_MESSAGES_H

#include <ultra64.h>


enum
{
    NET64_GAME_MSG_CUSTOM = 0,
    NET64_GAME_MSG_LOG_APPEND,   /* Append text to next log message */
    NET64_GAME_MSG_LOG_END,      /* Append text to log message and print it */

    NET64_GAME_MSG_COUNT
};

#endif
