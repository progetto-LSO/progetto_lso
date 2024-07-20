# Usa un'immagine base con gcc preinstallato
FROM gcc:12

# Installa le dipendenze di sistema
RUN apt-get update && apt-get install -y \
    libpq-dev

# Imposta la directory di lavoro
WORKDIR /app

# Copia il codice sorgente del programma
COPY . .

# Scarica wait-for-it
RUN curl -o /usr/local/bin/wait-for-it.sh https://raw.githubusercontent.com/vishnubob/wait-for-it/master/wait-for-it.sh \
    && chmod +x /usr/local/bin/wait-for-it.sh

# Compila il programma
RUN gcc -o my_program my_program.c -I/usr/include/postgresql -lpq

# Definisci il comando di default
CMD ["wait-for-it.sh", "postgres:5432", "--", "./my_program"]
