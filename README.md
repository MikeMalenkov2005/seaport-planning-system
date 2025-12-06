# Seaport Planning System

## Инициализация базы данных

Установка PostgreSQL:
`sudo apt install postgresql postgresql-contrib`

Настройка PostgreSQL:

`sudo nano /etc/postgresql/9.6/main/postgresql.conf`
-> найти строку `listen_addresses`  и задать = '*'

`sudo nano /etc/postgresql/9.6/main/pg_hba.conf`
-> найти строку `TYPE   DATABASE        USER            ADDRESS                 METHOD`

Добавить строку в начало:
```
host    all     database_administrator,app_user    0.0.0.0/0       md5
```
Изменить 
```
local   all             all                                     peer
```
на
```
local   all             all                                     md5
```
Добавить строки в конец:
```
host    all    all                  0.0.0.0/0       reject
host    all    all                  ::/0            reject
```

Перезапуск PostgreSQL:
`sudo systemctl restart postgresql`

Разместить файл setup_db.sh и дать права: chmod +x setup_db.sh
Запустить: sudo ./setup_db.sh
