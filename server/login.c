#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  long length = atol(getenv("CONTENT_LENGTH"));
  printf("Content-Type: text/plain\n");
  printf("Content-Length: %ld\n\n", length);
  while (length--) putchar(getchar());
}

