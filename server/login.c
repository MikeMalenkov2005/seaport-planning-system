#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char *length_string = getenv("CONTENT_LENGTH");
  long length = length_string ? atol(length_string) : 0;
  printf("Content-Type: text/plain\n\nMETHOD: %s\nURI: %s\nQUERY: %s\n",
      getenv("REQUEST_METHOD"), getenv("REQUEST_URI"), getenv("QUERY_STRING"));
  while (length--) putchar(getchar());
  return EXIT_SUCCESS;
}

