#include "files.h"

#include <stdlib.h>
#include <string.h>

int files_exists(const char *name)
{
  FILE *file = files_open(name, "r");
  return file ? (fclose(file), 1) : 0;
}

FILE *files_open(const char *name, const char *mode)
{
  static char path[1024];
  char *root = getenv("DOCUMENT_ROOT");
  return root ? fopen(strcat(strcat(strcpy(path, root), "/"), name), mode) : NULL;
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

void files_print_lines(const char *name, int first, int last)
{
  int c, l = 0;
  FILE *file = files_open(name, "r");
  if (file)
  {
    while ((c = fgetc(file)) != EOF)
    {
      if (l >= first && l <= last) putchar(c);
      if (c == '\n') ++l;
    }
    fclose(file);
  }
}

