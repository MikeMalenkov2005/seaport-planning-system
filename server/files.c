#include "files.h"

#include <stdlib.h>
#include <string.h>

FILE *files_open(const char *name, const char *mode)
{
  static char path[1024];
  char *root = getenv("DOCUMENT_ROOT");
  return root ? fopen(strcat(strcpy(path, root), name), mode) : NULL;
}

void files_print(const char *name)
{
  int c;
  FILE *file = files_open(name, "r");
  if (file)
  {
    while ((c = fgetc(file)) != EOF) putchar(c);
    fclose(file);
  }
}

