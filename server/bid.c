#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "db.h"
#include "form.h"
#include "input.h"
#include "session.h"

static int add_bid(const char *form)
{
  const char *args[29];
  PGresult *res;
  int lens[29], formats[29] = { 0 };
  int argnum = 1, result = 0;
  const char *key = form_next_key(form);
  if (key && db_init()) while (key)
  {
    if (!strcmp(key, "organization"))
      if ((args[0] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "INN"))
      if ((args[1] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "phone"))
      if ((args[2] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "mail"))
      if ((args[3] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "cargo_name"))
      if ((args[4] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "TNVED"))
      if ((args[5] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "direction"))
      if ((args[6] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "length"))
      if ((args[7] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "width"))
      if ((args[8] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "height"))
      if ((args[9] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "weight"))
      if ((args[10] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "package"))
      if ((args[11] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "characteristics"))
      if ((args[12] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "transport_in"))
      if ((args[13] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "transport_out"))
if ((args[14] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "date_out"))
      if ((args[15] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "date_in"))
      if ((args[16] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "store"))
      if ((args[17] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "term"))
      if ((args[18] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "demand"))
      if ((args[19] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "creator"))
      if ((args[20] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "sender"))
      if ((args[21] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "send_port"))
      if ((args[22] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "send_country"))
      if ((args[23] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "get_port"))
      if ((args[24] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "get_country"))
      if ((args[25] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "getter"))
      if ((args[26] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "other")) args[27] = form_clone(form, key);
    if (!strcmp(key, "quantity"))
      if ((args[28] = form_clone(form, key))) ++argnum;
    key = form_next_key(NULL);
  }
  if (argnum == sizeof(args) / sizeof(*args))
  {
    while (argnum--) lens[argnum] = args[argnum] ? strlen(args[argnum]) : 0;
    res = PQexecParams(db_conn(), "INSERT INTO application (name_organization,"
        "inn_organization, contact_phone, email, cargo_name, tn_code,"
        "id_direction, unit_length, unit_width, unit_height, unit_mass,"
        "cargo_packaging, structural_characteristics, id_transport_way_in,"
        "id_transport_way_out, pickup_date, import_date, id_warehouse_type,"
        "shelf_life, packaging_requirements, manufacturer, shipper,"
        "departure_port, departure_country, destination_port,"
        "destination_country, receiver, instructions_info, unit_count,"
        "id_application_status) VALUES ($1, $2, $3, $4, $5, $6, (SELECT "
        "id_direction FROM direction WHERE name = $7), $8, $9, $10, $11, $12,"
        "$13, (SELECT id_transport_way FROM transport_way WHERE name = $14),"
        "(SELECT id_transport_way FROM transport_way WHERE name = $15), $16,"
        "$17, (SELECT id_warehouse_type FROM warehouse_type WHERE name = $18),"
        "$19, $20, $21, $22, $23, $24, $25, $26, $27, $28, $29, 3);",
        sizeof(args) / sizeof(*args), NULL, args, lens, formats, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr,
          "INSERT INTO applications FAILED: %s\n", PQresultErrorMessage(res));
    }
    else result = 1;
  }
  for (argnum = sizeof(args) / sizeof(*args); argnum--;)
  {
    if (args[argnum]) free((void*)args[argnum]);
  }
  return result;
}

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

static void print_bids(int offset, int limit)
{
  char buffers[2][16];
  const char *args[2];
  int lens[2], formats[2] = { 0 };
  PGresult *res = NULL;
  int i;
  putchar('[');
  if (offset >= 0 && limit > 0 && db_init())
  {
    lens[0] = sprintf(buffers[0], "%d", offset);
    lens[1] = sprintf(buffers[1], "%d", limit);
    res = PQexecParams(db_conn(),
        "SELECT * FROM application OFFSET $1 LIMIT $2;",
        2, NULL, args, lens, formats, 0);
  }
  else if (limit < 0 && db_init())
  {
    res = PQexec(db_conn(), "SELECT * FROM application;");
  }
  if (res && PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr,
        "SELECT FROM application FAILED: %s\n", PQresultErrorMessage(res));
  }
  else if (res) for (i = 0; i < PQntuples(res); ++i)
  {
    if (i) putchar(',');
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
  putchar(']');
}

int main(void)
{
  char buffers[2][16];
  char *input = load_input();
  char *query = getenv("QUERY_STRING");
  char *method = getenv("REQUEST_METHOD");
  char *cookie = getenv("HTTP_COOKIE");
  char *token = cookie ? strstr(cookie, "token=") : NULL;
  char *username = NULL;
  char *offset, *limit;
  if (token)
  {
    token = strchr(token, '=') + 1;
    if (!session_is_token_valid(token)) token = NULL;
    else username = session_get_username(token);
  }
  if (username)
  {
    if (!strcmp(method, "GET"))
    {
      offset = form_get(buffers[0], sizeof(buffers[0]), query, "offset");
      limit = form_get(buffers[0], sizeof(buffers[0]), query, "limit");
      printf("Content-Type: application/json\n\n");
      print_bids(offset ? atoi(offset) : 0, limit ? atoi(limit) : -1);
    }
    else if (!strcmp(method, "POST"))
    {
      if (add_bid(input))
      {
        session_redirect_home(NULL);
      }
      else printf("Status: 409 Conflict\n\n");
    }
    else printf("Status: 400 Bad Request\n\n");
  }
  else printf("Status: 403 Forbidden\n\n");
  free_input(input);
  db_terminate();
  return EXIT_SUCCESS;
}


