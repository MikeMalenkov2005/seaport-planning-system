#ifndef _FORM_H
#define _FORM_H

#include <stddef.h>

char *form_get(char *buffer, size_t size, const char *form, const char *key);

size_t form_get_length(const char *form, const char *key);

#endif

