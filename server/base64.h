#ifndef _BASE64_H
#define _BASE64_H

#include <stddef.h>

char *base64_encode(char *buffer, size_t size, const char *plain);

char *base64_decode(char *buffer, size_t size, const char *encoded);

#endif

