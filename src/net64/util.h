#ifndef NET64_UTIL_H
#define NET64_UTIL_H

#include <ultra64.h>


void* memset(void* buf, int ch, size_t n);

char* strncpy(char* destination, const char* source, size_t max_len);

size_t strnlen(const char* str, size_t max_len);

#endif 
