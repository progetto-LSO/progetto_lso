# Dockerfile per il server
FROM gcc:latest

# Installa le dipendenze di sistema
RUN apt-get update && apt-get install -y \
    libpq-dev \
    libcjson-dev \
    postgresql-client

# Crea le directory di lavoro
RUN mkdir -p /app/server/src /app/server/build /app/server/include \
    /app/database/src /app/database/include \
    /app/config

# Imposta la directory di lavoro
WORKDIR /app

# Copia il contenuto delle directory nei rispettivi percorsi
COPY src /app/server/src
COPY include /app/server/include

COPY wait-for-postgres.sh .
RUN chmod +x wait-for-postgres.sh

EXPOSE 8080