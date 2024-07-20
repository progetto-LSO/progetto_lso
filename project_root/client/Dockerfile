# Dockerfile per il client
FROM gcc:latest

# Installa le dipendenze di sistema
RUN apt-get update && apt-get install -y \
    libpq-dev \
    libcjson-dev

# Crea le directory di lavoro
RUN mkdir -p /app/client/src /app/client/build /app/client/include \
    /app/config

# Imposta la directory di lavoro
WORKDIR /app

# Copia il contenuto delle directory nei rispettivi percorsi
COPY ./src /app/client/src
COPY ./include /app/client/include

COPY ../config /app/config

# Copia il Makefile nella directory di lavoro
COPY ../Makefile /app

# Compila il client
RUN make client

