#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "db.h"
#include "form.h"
#include "files.h"
#include "session.h"

int main(void)
{
  static char buffers[2][256];
  char *query = getenv("QUERY_STRING");
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  char *filename = NULL;
  size_t len = query ? form_get_length(query, "page") : 0;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (token && len && len < sizeof(buffers[1]) - 10 && !strcmp(method, "GET"))
  {
    filename = form_get(buffers[0], sizeof(buffers[0]), query, "page");
    if (filename)
    {
      filename = strcat(strcat(strcpy(buffers[1], "html/"), filename), ".html");
      if (files_exists(filename))
      {
        printf("Content-Type: text/html\n\n");
        files_print(filename);
      }
      else printf("Status: 404 Not Found\n\n");
    }
    else printf("Status 400 Bad Request\n\n");
  }
  else if (username) printf("Status: 400 Bad Request\n\n");
  else printf("Status: 403 Forbidden\n\n");
  db_terminate();
  return EXIT_SUCCESS;
}

