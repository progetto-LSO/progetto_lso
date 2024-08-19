# Dockerfile per il server
FROM gcc:latest

# Installa le dipendenze di sistema
RUN apt-get update && apt-get install -y \
    libpq-dev \
    libcjson-dev \
    tree

# Crea le directory di lavoro
RUN mkdir -p /app/library_admin/src /app/library_admin/build /app/library_admin/include

# Imposta la directory di lavoro
WORKDIR /app

# Copia il contenuto delle directory nei rispettivi percorsi
COPY src /app/library_admin/src
COPY include /app/library_admin/include

CMD ["/bin/bash", "-c", "make run_library_admin"]