# Seaport Planning System

## Инициализация базы данных

Установка PostgreSQL:
`sudo apt install postgresql postgresql-contrib`

Настройка PostgreSQL:

`sudo nano /etc/postgresql/9.6/main/postgresql.conf`
-> найти строку `listen_addresses`  и задать = '*'

```
sudo -u postgres psql -c "CREATE ROLE gui_design_specialist LOGIN PASSWORD 'password';"
sudo -u postgres psql -c "CREATE ROLE web_and_multimedia_developer LOGIN PASSWORD 'password';"
sudo -u postgres psql -c "CREATE ROLE database_administrator LOGIN PASSWORD 'password' CREATEDB CREATEROLE;"
sudo -u postgres psql -c "CREATE ROLE app_user LOGIN PASSWORD 'user_password';"
```

`sudo nano /etc/postgresql/9.6/main/pg_hba.conf`
-> найти строку `TYPE   DATABASE        USER            ADDRESS                 METHOD`

Добавить строку в начало:
```
host    all     database_administrator,web_and_multimedia_developer,app_user    0.0.0.0/0       md5
```

Добавить строки в конец:
```
host    all    all                  0.0.0.0/0       reject
host    all    all                  ::/0            reject
```

Перезапуск PostgreSQL:
`sudo systemctl restart postgresql`

Создание базы данных:
`sudo -u postgres psql -c "CREATE DATABASE project_db OWNER database_administrator;`

Инициализация пользователей базы данных:
```
sudo -u postgres psql -d project_db

GRANT CONNECT ON DATABASE project_db TO app_user;
GRANT USAGE ON SCHEMA public TO app_user;

GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO app_user;
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA public TO app_user;

ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT, INSERT, UPDATE, DELETE ON TABLES TO app_user;

ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT USAGE, SELECT ON SEQUENCES TO app_user;
GRANT ALL PRIVILEGES ON DATABASE project_db TO database_administrator;
```

Создание таблиц базы данных (init.sql рядом):
`PGPASSWORD=password psql -h <ip> -U database_administrator -d project_db -f init.sql`
