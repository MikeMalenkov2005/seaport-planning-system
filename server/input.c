#include "input.h"

#include <stdio.h>
#include <stdlib.h>

char *load_input(void)
{
  char *input = NULL;
  char *length_string = getenv("CONTENT_LENGTH");
  size_t length = length_string ? (size_t)atol(length_string) : 0;
  if (length && (input = malloc(length + 1)))
  {
    fread(input, length, 1, stdin);
    input[length] = 0;
  }
  return input;
}

void free_input(char *input)
{
  if (input) free(input);
}

