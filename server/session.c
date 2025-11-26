#include "session.h"
#include <string.h>

static char token_buffer[1024];

char *session_new_token(const char *username, const char *password)
{
  return strcat(strcat(strcpy(token_buffer, username), "\n"), password);
}

int session_is_token_valid(const char *token)
{
  return token && 1;
}

char *session_get_username(const char *token)
{
  return strtok(strcpy(token_buffer, token), "\n");
}

