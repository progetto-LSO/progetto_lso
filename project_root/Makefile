# Variabili per le directory
SERVER_SRC = server/src
SERVER_BUILD = server/build

DATABASE_SRC = database/src

CONFIG_SRC = config

# Compilatore e flag
CC = gcc
CFLAGS = -Wextra -Wall -I/usr/include/postgresql
LDFLAGS = -lpq -ljson-c

# Obiettivi
all: clean server

server: $(SERVER_BUILD)/server


.PHONY: clean

# Regola generica per compilare i file .c del server
$(SERVER_BUILD)/server: $(wildcard $(SERVER_SRC)/*.c) $(wildcard $(DATABASE_SRC)/*.c) $(wildcard $(CONFIG_SRC)/*.c)
	mkdir -p $(SERVER_BUILD)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


# Pulizia dei file compilati
clean:
	rm -rf $(SERVER_BUILD)/*
	rm -rf $(CLIENT_BUILD)/*

clean_server:
	rm -rf $(SERVER_BUILD)/*


