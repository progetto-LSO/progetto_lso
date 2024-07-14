# Variabili per le directory
SERVER_SRC = server/src
SERVER_BUILD = server/build

CLIENT_SRC = client/src
CLIENT_BUILD = client/build

DATABASE_SRC = database/src
DATABASE_BUILD = database/build

# Compilatore e flag
CC = gcc
CFLAGS = -I/usr/include/postgresql -lpq

# Obiettivi
all: clean server client database

server: $(SERVER_BUILD)/server.o

client: $(CLIENT_BUILD)/client.o

.PHONY: clean

# Regola generica per compilare i file .c
$(SERVER_BUILD)/server.o: $(wildcard $(SERVER_SRC)/*.c) $(wildcard $(DATABASE_SRC)/*.c)
	mkdir -p $(SERVER_BUILD)
	$(CC) -o $@ $^ $(CFLAGS)

$(CLIENT_BUILD)/client.o: $(wildcard $(CLIENT_SRC)/*.c)
	mkdir -p $(CLIENT_BUILD)
	$(CC) -o $@ $^ $(CFLAGS)


# Pulizia dei file compilati
clean:
	rm -rf $(SERVER_BUILD)/*
	rm -rf $(CLIENT_BUILD)/*
	rm -rf $(DATABASE_BUILD)/*

# Regola per avviare server.o
run_server: server
	$(SERVER_BUILD)/server.o