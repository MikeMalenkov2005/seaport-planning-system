#include "db.h"
#include "form.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>

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
        "SELECT (e.surname, e.name, e.patronymic, j.name) FROM employee AS e"
        "JOIN job_title AS j ON e.id_job_title = j.id_job_title"
        "WHERE e.login = $1 LIMIT 1;",
        1, NULL, &username, &p_length, &p_format, 0);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
      fprintf(stderr,
          "SELECT FROM employee JOIN job_title BY login FAILED: %s\n",
          PQresultErrorMessage(res));
    }
    if (PQntuples(res) > 0 && PQnfields(res) == 4)
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
  }
  putchar('}');
}

int db_add_bid(const char *form)
{
  const char *args[29];
  PGresult *res;
  int lens[29], formats[29] = { 0 };
  int argnum = 0, result = 0;
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
    if (!strcmp(key, "other"))
      if ((args[27] = form_clone(form, key))) ++argnum;
    if (!strcmp(key, "quantity"))
      if ((args[28] = form_clone(form, key))) ++argnum;
  }
  if (argnum == sizeof(args) / sizeof(*args))
  {
    while (argnum--) lens[argnum] = strlen(args[argnum]);
    res = PQexecParams(conn, "INSERT INTO application (name_organization,"
        "inn_organization, contact_phone, email, cargo_name, tn_code,"
        "id_direction, unit_length, unit_width, unit_height, unit_mass,"
        "cargo_packaging, structural_characteristics, id_transport_way_in,"
        "id_transport_way_out, pickup_date, import_date, id_warehouse_type,"
        "shelf_life, packaging_requirements, manufacturer, shipper,"
        "departure_port, departure_country, destination_port,"
        "destination_country, receiver, instructions_info, unit_count"
        "id_application_status) VALUES ($1, $2, $3, $4, $5, $6, (SELECT "
        "id_direction FROM direction WHERE name = $7), $8, $9,"
        "$10, $11, $12, $13, (SELECT id_transport_way FROM transport_way "
        "WHERE id_transport_way = $14), (SELECT id_transport_way FROM "
        "transport_way WHERE id_transport_way = $15), $16, $17,"
        "(SELECT id_warehouse_type FROM warehouse_type WHERE name = $18),"
        "$19, $20, 21, $22, $23, $24, $25, $26, $27, $28, $29, 3);",
        sizeof(args) / sizeof(*args), NULL, args, lens, formats, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
      fprintf(stderr,
          "INSERT INTO applications FAILED: %s\n", PQresultErrorMessage(res));
    }
    else result = 1;
  }
  return result;
}

