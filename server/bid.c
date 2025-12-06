#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "db.h"
#include "input.h"
#include "session.h"

int main(void)
{
  char *input = load_input();
  /* char *query = getenv("QUERY_STRING"); */
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
  if (username)
  {
    if (!strcmp(method, "POST"))
    {
      session_redirect_home(NULL);
      db_add_bid(input);
    }
    else printf("Status: 400 Bad Request\n\n");
  }
  else printf("Status: 403 Forbidden\n\n");
  free_input(input);
  db_terminate();
  return EXIT_SUCCESS;
}


