#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "session.h"
#include "db.h"

int main(void)
{
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (username)
  {
  }
  printf("Status: 303 See Other\n");
  printf("Location: /login.cgi\n\n");
  db_terminate();
  return EXIT_SUCCESS;
}

