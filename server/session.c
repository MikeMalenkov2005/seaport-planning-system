#include "session.h"

#include "base64.h"
#include "db.h"

#include <string.h>
#include <stdio.h>
#include <time.h>

static char token_buffer[1024];

char *session_new_token(const char *username, const char *password)
{
  static char token[1024];
  time_t t = time(NULL);
  int size = sprintf(token_buffer, "%s\n%s\n%lu", username, password, t);
  token_buffer[size] = 0;
  return base64_encode(token, sizeof(token), token_buffer);
}

int session_is_token_valid(const char *token)
{
  double dt;
  char *tstr;
  time_t t;
  char *data = base64_decode(token_buffer, sizeof(token_buffer), token);
  int user;
  if (!data || db_is_token_blacklisted(token)) return 0;
  if ((user = db_find_user(strtok(data, "\n"))) == -1) return 0;
  if (!db_is_password_valid(user, strtok(NULL, "\n"))) return 0;
  if (!(tstr = strtok(NULL, "\n"))) return 0;
  if (sscanf(tstr, "%lu", &t) != 1) return 0;
  dt = difftime(time(NULL), t);
  return dt >= 0 && dt < 86400;
}

char *session_get_username(const char *token)
{
  char *data = base64_decode(token_buffer, sizeof(token_buffer), token);
  return data ? strtok(data, "\n") : NULL;
}

void session_redirect_home(const char *new_token)
{
  printf("Status: 303 See Other\n");
  if (new_token) printf("Set-Cookie: token=%s; Max-Age=86400; Path=/; HttpOnly; Secure\n", new_token);
  printf("Location: /html.cgi?page=BidList\n\n");
}

