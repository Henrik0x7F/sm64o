#ifndef NET64_LOGGING_H
#define NET64_LOGGING_H

#include "net64/net64.h"

/* Sends log message into the client's console
 * Returns 1 on success & 0 on error
 */
int net64_log(const char* log_message);

#endif
