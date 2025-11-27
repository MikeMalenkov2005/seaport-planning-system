#include "session.h"

#include <string.h>
#include <stdio.h>
#include <time.h>

static char token_buffer[1024];

char *session_new_token(const char *username, const char *password)
{
  time_t t = time(NULL);
  int size = sprintf(token_buffer, "%s\n%s\n%lu", username, password, t);
  token_buffer[size] = 0;
  return token_buffer;
}

int session_is_token_valid(const char *token)
{
  double dt;
  char *tstr;
  time_t t;
  if (!strtok(strcpy(token_buffer, token), "\n")) return 0;
  if (!strtok(NULL, "\n")) return 0;
  if (!(tstr = strtok(NULL, "\n"))) return 0;
  if (sscanf(tstr, "%lu", &t) != 1) return 0;
  dt = difftime(t, time(NULL));
  return dt >= 0 && dt < 86400;
}

char *session_get_username(const char *token)
{
  return strtok(strcpy(token_buffer, token), "\n");
}

