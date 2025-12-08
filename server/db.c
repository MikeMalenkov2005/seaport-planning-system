#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static PGconn *conn;

int db_init(void)
{
  if (conn) return 1;
  /* TODO: For real project / remote database the password should be hidden */
  conn = PQconnectdb(
      "postgresql://database_administrator:password@localhost:5432/project_db");
  if (PQstatus(conn) != CONNECTION_OK)
  {
    fprintf(stderr, "Database connection failed: %s\n", PQerrorMessage(conn));
    PQfinish(conn);
    conn = NULL;
    return 0;
  }
  return 1;
}

PGconn *db_conn(void)
{
  return conn;
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
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr,
          "SELECT FROM employee BY login FAILED: %s\n",
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
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr,
          "SELECT FROM employee BY id_employee FAILED: %s\n",
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
  PGresult *res;
  int p_length, p_format = 0, result = 0;
  if (token && db_init())
  {
    p_length = strlen(token);
    res = PQexecParams(conn,
        "SELECT id FROM blacklisted_tokens WHERE token = $1;",
        1, NULL, &token, &p_length, &p_format, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr,
          "SELECT FROM blacklisted_tokens BY token FAILED: %s\n",
          PQresultErrorMessage(res));
    }
    else if (PQntuples(res) > 0) result = 1;
    PQclear(res);
  }
  return result;
}

void db_blacklist_token(const char *token)
{
  (void)token;
}

void db_print_user_info(const char *username)
{
  PGresult *res;
  int p_length, p_format = 0, count = 0;
  putchar('{');
  if (username && db_init())
  {
    p_length = strlen(username);
    res = PQexecParams(conn,
        "SELECT e.surname, e.name, e.patronymic, j.name FROM employee AS e "
        "JOIN job_title AS j ON e.id_job_title = j.id_job_title "
        "WHERE e.login = $1 LIMIT 1;",
        1, NULL, &username, &p_length, &p_format, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr,
          "SELECT FROM employee JOIN job_title BY login FAILED: %s\n",
          PQresultErrorMessage(res));
    }
    if (PQntuples(res) == 1 && PQnfields(res) == 4)
    {
      if (PQgetvalue(res, 0, 0))
      {
        if (count++) putchar(',');
        printf("\"surname\":\"%s\"", PQgetvalue(res, 0, 0));
      }
      if (PQgetvalue(res, 0, 1))
      {
        if (count++) putchar(',');
        printf("\"name\":\"%s\"", PQgetvalue(res, 0, 1));
      }
      if (PQgetvalue(res, 0, 2))
      {
        if (count++) putchar(',');
        printf("\"patronym\":\"%s\"", PQgetvalue(res, 0, 2));
      }
      if (PQgetvalue(res, 0, 3))
      {
        if (count++) putchar(',');
        printf("\"role\":\"%s\"", PQgetvalue(res, 0, 3));
      }
    }
    PQclear(res);
  }
  putchar('}');
}

