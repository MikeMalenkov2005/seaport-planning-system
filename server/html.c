#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "form.h"
#include "files.h"
#include "session.h"

int main(void)
{
  static char buffer[256];
  char *query = getenv("QUERY_STRING");
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  char *filename = NULL;
  size_t fn_len = query ? form_get_length(query, "page") : 0;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (username && fn_len && fn_len < sizeof(buffer) - 5 && !strcmp(method, "GET"))
  {
    filename = strcat(form_get(buffer, sizeof(buffer), query, "page"), ".html");
    if (files_exists(filename))
    {
      printf("Content-Type: text/html\n\n");
      files_print(filename);
    }
    else printf("Status: 404 Not Found\n\n");
  }
  else if (username) printf("Status: 400 Bad Request\n\n");
  else printf("Status: 403 Forbidden\n\n");
  return EXIT_SUCCESS;
}

