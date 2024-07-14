# Progetto LSO

## Setup Database
Accedi a postgres con `su - postgres`

Avvia `psql`

Esegui la query 
```sql
CREATE DATABASE library;
```

Connettiti al database con `\c library`

Inserisci le tabelle eseguendo il codice SQL del file `tables.sql`

Inserisci le view eseguendo il codice SQL del file `views.sql`

Inserisci i trigger eseguendo il codice SQL del file `triggers.sql`

Inserisci libri eseguendo il codice SQL del file `book_insert.sql`