#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "form.h"
#include "files.h"
#include "input.h"
#include "session.h"

void redirect_loggedin_user(const char *username, const char *new_token)
{
  (void)username;
  printf("Status: 303 See Other\n");
  if (new_token) printf("Set-Cookie: token=%s; Max-Age=86400; Path=/; HttpOnly; Secure\n", new_token);
  printf("Location: /html.cgi?page=BidList\n\n");
}

int main(void)
{
  static char buffers[2][32];
  char *input = load_input();
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  char *password = NULL;
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
    else redirect_loggedin_user(username, NULL);
  }
  else if (!strcmp(method, "POST"))
  {
    fprintf(stderr, "RQ: '%s' \n", input);
    username = form_get(buffers[0], sizeof(buffers[0]), input, "username");
    password = form_get(buffers[1], sizeof(buffers[1]), input, "password");
    if (username && strlen(username) > 16) username = NULL;
    if (password && strlen(password) > 16) password = NULL;
    token = session_new_token(username, password);
    if (!token || !session_is_token_valid(token))
    {
      printf("Content-Type: text/html\n\n");
      files_print("html/Authorization.html");
    }
    else redirect_loggedin_user(username, token);
  }
  else
  {
    printf("Status: 403 Forbidden\n\n");
  }
  free_input(input);
  db_terminate();
  return EXIT_SUCCESS;
}

