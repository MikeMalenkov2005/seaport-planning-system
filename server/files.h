#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>

FILE *files_open(const char *name, const char *mode);

void files_print(const char *name);

#endif

