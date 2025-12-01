# Seaport Planning System

## Инициализация базы данных

Установка PostgreSQL:
`sudo apt install postgresql postgresql-contrib`

Настройка PostgreSQL:

`sudo nano /etc/postgresql/9.6/main/postgresql.conf`
-> найти строку `listen_addresses`  и задать = '*'

Создание пользователей и ролей:
```
sudo -u postgres psql -c "CREATE ROLE database_administrator LOGIN PASSWORD 'password';"
sudo -u postgres psql -c "CREATE ROLE developers;"

sudo -u postgres psql -c "CREATE ROLE regular_user LOGIN PASSWORD 'user_password';"
sudo -u postgres psql -c "CREATE ROLE app_user;"
```

`sudo nano /etc/postgresql/9.6/main/pg_hba.conf`
-> найти строку `TYPE   DATABASE        USER            ADDRESS                 METHOD`

Добавить строку в начало:
```
host    all     database_administrator,app_user    0.0.0.0/0       md5
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

Создание прав:
```
sudo -u postgres psql -d project_db -c "GRANT CONNECT ON DATABASE project_db TO app_user;"

sudo -u postgres psql -d project_db -c "GRANT USAGE ON SCHEMA public TO app_user;"

sudo -u postgres psql -d project_db -c "GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO app_user;"

sudo -u postgres psql -c "GRANT app_user TO regular_user;"

sudo -u postgres psql -c "GRANT CONNECT ON DATABASE project_db TO developers;"

sudo -u postgres psql project_db -c "ALTER SCHEMA public OWNER TO developers;"

sudo -u postgres psql project_db -c "GRANT CREATE ON SCHEMA public TO developers;"

sudo -u postgres psql project_db -c "GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO developers;"

sudo -u postgres psql project_db -c "ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT, INSERT, UPDATE, DELETE ON TABLES TO developers;"
```
Подтверждение прав (дать юзеру роль):
```
sudo -u postgres psql -c "GRANT app_user TO regular_user;"

sudo -u postgres psql -c "GRANT developers TO database_administrator;"
```
Создание таблиц базы данных (init.sql рядом):
`PGPASSWORD=password psql -h <ip> -U database_administrator -d project_db -f init.sql`
Аналогично с заполнением базы данных