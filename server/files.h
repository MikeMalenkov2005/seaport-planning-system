#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>

int files_exists(const char *name);

FILE *files_open(const char *name, const char *mode);

void files_print(const char *name);

void files_print_lines(const char *name, int first, int last);

#endif

