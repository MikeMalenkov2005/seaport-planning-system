#ifndef _JSON_H
#define _JSON_H

#include <stddef.h>

char *json_get(char *buffer, size_t size, const char *json, const char *path);

#endif

