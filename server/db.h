#ifndef _DB_H
#define _DB_H

#include <postgresql/libpq-fe.h>

int db_init(void);

PGconn *db_conn(void);

void db_terminate(void);

int db_find_user(const char *username);

int db_is_password_valid(int user, const char *password);

int db_is_token_blacklisted(const char *token);

void db_print_user_info(const char *username);

#endif

