#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "session.h"
#include "db.h"

static void delete_token(const char *token)
{
  PGresult *res;
  int len = strlen(token), format = 0;
  if (token && db_init())
  {
    res = PQexecParams(db_conn(),
        "INSERT INTO blacklisted_tokens (token) VALUES ($1);",
        1, NULL, &token, &len, &format, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr,
          "INSERT INTO blacklisted_tokens FAILED: %s",
          PQresultErrorMessage(res));
    }
    PQclear(res);
  }
}

int main(void)
{
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
  }
  delete_token(token);
  printf("Status: 303 See Other\n");
  printf("Location: /login.cgi\n\n");
  db_terminate();
  return EXIT_SUCCESS;
}

