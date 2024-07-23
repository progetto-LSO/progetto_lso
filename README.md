# Progetto LSO
## Componenti del gruppo
Ingenito Roberto - N86004077

Ingenito Simone - N86004063

Sequino Lorenzo - N86004367

## Documentazione
[Link documentazione](/documentazione/documentazione.pdf)

## Avvio con Docker Compose
Spostati nella cartella `project_root`

0. Esegui il build:
    ```sh
    docker compose build
    ```

L'avvio dei container dev'essere fatto in sessioni diverse del terminale<br/>
Altrimenti è possibile accompagnare il comando con `-d` (*detach*) per avviare il container e liberare il terminale.

1. Avvia il container del database:
    ```sh
    docker compose up database
    ```

1. Avvia il container del server:

    > Aspetta che il container del database riporti il messaggio "**database system is ready to accept connections**"
    ```sh
    docker compose up server
    ```

1. Avvia un'istanza del client:

    > Aspetta prima l'avvio del server

    ```sh
    ./run_docker_client.sh
    ```
