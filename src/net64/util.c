#include "net64/util.h"

#include <string.h>


void* memset(void* buf, int ch, size_t n)
{
    size_t i = 0;
    while(i < n)
    {
        ((char*)buf)[i] = (char)ch;
        ++i;
    }

    return buf;
}

char* strncpy(char* destination, const char* source, size_t max_len)
{
    size_t len = strnlen(source, max_len);
    memcpy(destination, source, len);
    return (char*)memset(destination + len, 0, max_len - len);
}

size_t strnlen(const char* str, size_t max_len)
{
    size_t len = 0;
    while(len < max_len && str[len] != '\0')
    {
        ++len;
    }
    return len;
}
