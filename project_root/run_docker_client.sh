#!/bin/bash

# Controlla se il servizio è in esecuzione
SERVICE_RUNNING=$(docker compose ps --services --filter "status=running" | grep -w "client")

if [ -z "$SERVICE_RUNNING" ]; then
    echo "Il servizio client non è in esecuzione."
    echo "Avvio del servizio..."

    # Avvia il servizio client in modalità detached
    docker compose up client -d

    # Attendi un po' di tempo per dare al servizio il tempo di avviarsi
    sleep 3

fi

clear;

# Esegui il comando nel container
docker compose exec client /bin/bash -c "client/build/client.o"
