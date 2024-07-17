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

## Installa le dipendenze
### Postgres
```sh
sudo apt-get install libpq-dev
```

### cJSON
```sh
sudo apt update
sudo apt upgrade
sudo apt install build-essential cmake
sudo apt install git
git clone https://github.com/DaveGamble/cJSON.git
cd cJSON
mkdir build
cd build
cmake ..
make
sudo make install
cd ../../
rm -rf cJSON
sudo ldconfig -v
```