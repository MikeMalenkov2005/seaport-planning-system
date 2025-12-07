#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "db.h"
#include "form.h"
#include "input.h"
#include "session.h"

static void print_bid(const char *id)
{
  int len = strlen(id), format = 0;
  const char *value;
  PGresult *res;
  const int i = 0;
  res = PQexecParams(db_conn(),
      "SELECT * FROM application WHERE id_application = $1;",
      1, NULL, &id, &len, &format, 0);
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr,
        "SELECT FROM application FAILED: %s\n", PQresultErrorMessage(res));
  }
  else if (PQntuples(res) == 1)
  {
    putchar('{');
    if ((value = PQgetvalue(res, i, 0))) printf("\"id\":%s", value);
    if ((value = PQgetvalue(res, i, 1))) printf(",\"org\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 2))) printf(",\"inn\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 3))) printf(",\"phone\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 4))) printf(",\"email\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 6))) printf(",\"name\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 7))) printf(",\"tnved\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 8))) printf(",\"direction\":%s", value);
    if ((value = PQgetvalue(res, i, 9))) printf(",\"length\":%s", value);
    if ((value = PQgetvalue(res, i, 10))) printf(",\"width\":%s", value);
    if ((value = PQgetvalue(res, i, 11))) printf(",\"height\":%s", value);
    if ((value = PQgetvalue(res, i, 12))) printf(",\"weight\":%s", value);
    if ((value = PQgetvalue(res, i, 13))) printf(",\"count\":%s", value);
    if ((value = PQgetvalue(res, i, 14))) printf(",\"packaging\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 16))) printf(",\"characteristics\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 17))) printf(",\"transport_in\":%s", value);
    if ((value = PQgetvalue(res, i, 18))) printf(",\"transport_out\":%s", value);
    if ((value = PQgetvalue(res, i, 19))) printf(",\"date_in\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 20))) printf(",\"date_out\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 22))) printf(",\"warehouse_type\":%s", value);
    if ((value = PQgetvalue(res, i, 23))) printf(",\"shelf_life\":%s", value);
    if ((value = PQgetvalue(res, i, 24)))
    {
      printf(",\"demands\":\"");
      while (*value)
      {
        if (*value == '\n')
        {
          putchar('\\');
          putchar('n');
        }
        else putchar(*value);
        ++value;
      }
      putchar('\"');
    }
    if ((value = PQgetvalue(res, i, 25))) printf(",\"creator\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 26))) printf(",\"sender\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 27))) printf(",\"sender_port\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 28))) printf(",\"sender_country\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 29))) printf(",\"receiver_port\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 30))) printf(",\"receiver_country\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 31))) printf(",\"receiver\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 32)))
    {
      printf(",\"other\":\"");
      while (*value)
      {
        if (*value == '\n')
        {
          putchar('\\');
          putchar('n');
        }
        else putchar(*value);
        ++value;
      }
      putchar('\"');
    }
    if ((value = PQgetvalue(res, i, 33))) printf(",\"comment\":\"%s\"", value);
    if ((value = PQgetvalue(res, i, 34))) printf(",\"status\":\"%s\"", value);
    putchar('}');
  }
  else printf("Status: 404 Not Found\n\n");
}

int main(void)
{
  char buffer[2][64];
  char *input = load_input();
  char *query = getenv("QUERY_STRING");
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (!username) printf("Status: 403 Forbidden\n\n");
  else if (!strcmp(method, "POST"))
  {
    printf("Status: 501 Not Implemented\n\n");
  }
  else if (!strcmp(method, "GET") && form_get_length(query, "id"))
  {
    print_bid(form_get(buffer[0], sizeof(buffer[0]), query, "id"));
  }
  else printf("Status: 400 Bad Request\n\n");
  db_terminate();
  free_input(input);
  return EXIT_SUCCESS;
}

