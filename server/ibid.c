#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "db.h"
#include "form.h"
#include "input.h"
#include "session.h"

static void print_pair(const char *key, const char *value, int flags)
{
  if (key && value && *value)
  {
    if (!(flags & 2)) putchar(',');
    printf("\"%s\":", key);
    if (!(flags & 1))
    {
      putchar('\"');
      while (*value) switch (*value)
      {
      case '\r':
        putchar('\\');
        putchar('r');
        ++value;
      case '\n':
        putchar('\\');
        putchar('n');
        ++value;
        break;
      case '\"':
        putchar('\\');
      default:
        putchar(*value++);
        break;
      }
      putchar('\"');
    }
    else printf("%s", value);
  }
}

static void print_bid(const char *id)
{
  int len = strlen(id), format = 0;
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
    print_pair("id", PQgetvalue(res, i, 0), 3);
    print_pair("org", PQgetvalue(res, i, 1), 0);
    print_pair("inn", PQgetvalue(res, i, 2), 0);
    print_pair("phone", PQgetvalue(res, i, 3), 0);
    print_pair("email", PQgetvalue(res, i, 4), 0);
    print_pair("name", PQgetvalue(res, i, 5), 0);
    print_pair("tnved", PQgetvalue(res, i, 6), 0);
    print_pair("direction", PQgetvalue(res, i, 7), 1);
    print_pair("length", PQgetvalue(res, i, 8), 1);
    print_pair("width", PQgetvalue(res, i, 9), 1);
    print_pair("height", PQgetvalue(res, i, 10), 1);
    print_pair("weight", PQgetvalue(res, i, 11), 1);
    print_pair("count", PQgetvalue(res, i, 12), 1);
    print_pair("packaging", PQgetvalue(res, i, 13), 0);
    print_pair("characteristics", PQgetvalue(res, i, 15), 0);
    print_pair("transport_in", PQgetvalue(res, i, 16), 1);
    print_pair("transport_out", PQgetvalue(res, i, 17), 1);
    print_pair("date_out", PQgetvalue(res, i, 18), 0);
    print_pair("date_in", PQgetvalue(res, i, 19), 0);
    print_pair("warehouse_type", PQgetvalue(res, i, 21), 1);
    print_pair("shelf_life", PQgetvalue(res, i, 22), 1);
    print_pair("demands", PQgetvalue(res, i, 23), 0);
    print_pair("creator", PQgetvalue(res, i, 24), 0);
    print_pair("sender", PQgetvalue(res, i, 25), 0);
    print_pair("sender_port", PQgetvalue(res, i, 26), 0);
    print_pair("sender_country", PQgetvalue(res, i, 27), 0);
    print_pair("receiver_port", PQgetvalue(res, i, 28), 0);
    print_pair("receiver_country", PQgetvalue(res, i, 29), 0);
    print_pair("receiver", PQgetvalue(res, i, 30), 0);
    print_pair("other", PQgetvalue(res, i, 31), 0);
    print_pair("comment", PQgetvalue(res, i, 32), 0);
    print_pair("status", PQgetvalue(res, i, 33), 1);
    print_pair("worker", PQgetvalue(res, i, 34), 1);
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

