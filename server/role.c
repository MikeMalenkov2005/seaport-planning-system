#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "session.h"
#include "db.h"

int main(void)
{
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (username && !strcmp(method, "GET"))
  {
    printf("Content-Type: application/json\n\n");
    db_print_user_info(username);
  }
  else printf("Status: 403 Forbidden\n\n");
  db_terminate();
  return EXIT_SUCCESS;
}

