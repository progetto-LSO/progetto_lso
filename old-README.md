## Avvio da terminale
> Per avviare il progetto da terminale, bisogna cambiare alcuni valori:<br/>
vai in `config/database_config.h` e cambia *DB_HOST* in *localhost* e togli il commento a *DB_PORT* <br/>
vai in `config/address_config.h` e cambia *SERVER_ADDRESS* in *127.0.0.1*


Spostati nella cartella `project_root`

### Setup ambiente
1. Installa Postgres
    ```sh
    sudo apt install postgresql
    ```

1. Avvia il service di postgreso
    ```sh
    sudo systemctl start postgresql
    ```

1. Accedi a postgres con `su - postgres`

1. Avvia `psql` ed esegui la query per creare il database
    ```sql
    CREATE DATABASE library;
    ```

1. Connettiti al database con
    ```sql
    \c library;
    ```

1. Inserisci le tabelle eseguendo il codice SQL del file `tables.sql` ( `project_root/database/query` )

1. Inserisci le view eseguendo il codice SQL del file `views.sql`

1. Inserisci i trigger eseguendo il codice SQL del file `triggers.sql`

1. Inserisci libri eseguendo il codice SQL del file `book_insert.sql`

1. Installa le dipendenze
    ```sh
    sudo apt-get update && sudo apt-get install -y \
        gcc \
        libpq-dev \
        libcjson-dev;
    sudo ldconfig -v;
    ```
### Avvia il server
```sh
make run_server
```

### Avvia il client
```sh
make run_client
```