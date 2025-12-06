#ifndef _SESSION_H
#define _SESSION_H

char *session_new_token(const char *username, const char *password);

int session_is_token_valid(const char *token);

char *session_get_username(const char *token);

void session_redirect_home(const char *new_token);

#endif

