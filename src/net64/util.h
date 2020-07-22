#ifndef NET64_UTIL_H
#define NET64_UTIL_H

#include <ultra64.h>


void* memset(void* buf, int ch, size_t n);

/* Copies c string from source to destination. Stops after max_len bytes.
   Fills remaining bytes with zeros. Destination is always null terminated. */
char* strncpy(char* destination, const char* source, size_t max_len);

size_t strnlen(const char* str, size_t max_len);

#endif 
