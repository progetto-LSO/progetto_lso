# Progetto LSO

## Setup Database
Accedi a postgres con `su - postgres`

Avvia `psql`

Esegui la query 
```sql
CREATE DATABASE library;
```

Connettiti al database con `\c library`

Esegui la query 
```sql
CREATE TABLE "user" (
    user_id SERIAL PRIMARY KEY, 
    username TEXT UNIQUE NOT NULL, 
    passw TEXT NOT NULL
);

CREATE TABLE book (
    isbn TEXT PRIMARY KEY, 
    title TEXT UNIQUE NOT NULL, 
    authors TEXT[] NOT NULL, 
    genre TEXT[] NOT NULL, 
    quantity INTEGER NOT NULL,

    CONSTRAINT check_quantity_validity CHECK (quantity >= 0)
);

CREATE TABLE loan (
    loan_start TIMESTAMP WITH TIME ZONE  NOT NULL  DEFAULT CURRENT_TIMESTAMP,
    loan_end TIMESTAMP WITH TIME ZONE  NOT NULL,
    returned TIMESTAMP WITH TIME ZONE,

    user_id SERIAL, 
    isbn TEXT,

    CONSTRAINT loan_pk PRIMARY KEY (user_id, isbn),
    CONSTRAINT loan_user_fk FOREIGN KEY (user_id) REFERENCES "user" ON DELETE CASCADE,
    CONSTRAINT loan_book_fk FOREIGN KEY (isbn) REFERENCES book ON DELETE CASCADE,
    
    CONSTRAINT check_loan_validity CHECK (loan_end > loan_start)
);
```