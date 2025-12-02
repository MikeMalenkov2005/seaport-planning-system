#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>

static PGconn *conn;

int db_init(void)
{
  if (conn) return 1;
  conn = PQconnectdb("postgresql://regular_user@localhost?port=5432&dbname=project_db");
  if (PQstatus(conn) != CONNECTION_OK)
  {
    fprintf(stderr, "Database connection failed: %s\n", PQerrorMessage(conn));
    PQfinish(conn);
    conn = NULL;
    return 0;
  }
  return 1;
}

void db_terminate(void)
{
  if (conn)
  {
    PQfinish(conn);
    conn = NULL;
  }
}

int db_find_user(const char *username)
{
  PGresult *res;
  int p_length, p_format = 0, result = -1;
  if (username && db_init())
  {
    p_length = (int)strlen(username);
    res = PQexecParams(conn,
        "SELECT id_employee FROM employee WHERE login = $1 LIMIT 1;",
        1, NULL, &username, &p_length, &p_format, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr,
          "SELECT FROM employee BY login FAILED: %s",
          PQresultErrorMessage(res));
    }
    else if (PQntuples(res) == 1 && PQnfields(res) == 1)
    {
      result = atoi(PQgetvalue(res, 0, 0));
    }
    PQclear(res);
  }
  return result;
}

int db_is_password_valid(int user, const char *password)
{
  PGresult *res;
  char p_user_id[32] = { 0 };
  int p_length, p_format = 0, result = 0;
  const char *p_user_id_ptr = p_user_id;
  if (user != -1 && password && db_init())
  {
    p_length = sprintf(p_user_id, "%d", user);
    res = PQexecParams(conn,
        "SELECT password FROM employee WHERE id_employee = $1;",
        1, NULL, &p_user_id_ptr, &p_length, &p_format, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr,
          "SELECT FROM employee BY id_employee FAILED: %s",
          PQresultErrorMessage(res));
    }
    else if (PQntuples(res) == 1 && PQnfields(res) == 1)
    {
      result = !strcmp(password, PQgetvalue(res, 0, 0));
    }
    PQclear(res);
  }
  return result;
}

int db_is_token_blacklisted(const char *token)
{
}

