#!/bin/bash
set -e

psql -v ON_ERROR_STOP=1 --username "$POSTGRES_USER" <<-EOSQL
    ALTER USER postgres WITH PASSWORD 'admin';
EOSQL
