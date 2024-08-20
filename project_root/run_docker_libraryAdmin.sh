#!/bin/bash

# Controlla se il servizio è in esecuzione
SERVICE_RUNNING=$(docker compose ps --services --filter "status=running" | grep -w "library_admin")

if [ -z "$SERVICE_RUNNING" ]; then
    echo "Il servizio library_admin non è in esecuzione."
    echo "Avvio del servizio..."

    # Avvia il servizio library_admin in modalità detached
    docker compose up library_admin -d

    # Attendi un po' di tempo per dare al servizio il tempo di avviarsi
    sleep 3

fi

clear;

# Esegui il comando nel container
docker compose exec library_admin /bin/bash -c "library_admin/build/library_admin.o"
