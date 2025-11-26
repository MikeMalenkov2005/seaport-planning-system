#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "session.h"

static char path_buffer[1024];

int main(void)
{
  FILE *f;
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = NULL;/* cookie ? strstr(cookie, "token=") : NULL; */
  char *username = NULL;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (!strcmp(method, "GET"))
  {
    if (!username)
    {
      printf("Content-Type: text/html\n\n");
      files_print("html/Authorization.html");
    }
    else printf("Status: 303 See Other\nLocation: /%s\n\n", username);
  }
  else
  {
    printf("Status: 403 Forbidden\n\n");
  }
  return EXIT_SUCCESS;
}

