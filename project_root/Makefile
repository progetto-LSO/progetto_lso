# Variabili per le directory
SERVER_SRC = server/src
SERVER_BUILD = server/build

CLIENT_SRC = client/src
CLIENT_BUILD = client/build

LIBRARY_ADMIN_SRC = library_admin/src
LIBRARY_ADMIN_BUILD = library_admin/build

DATABASE_SRC = database/src

CONFIG_SRC = config

# Compilatore e flag
CC = gcc
CFLAGS = -Wextra -Wall -I/usr/include/postgresql -lpq -lcjson

# Obiettivi
all: clean server client library_admin

server: $(SERVER_BUILD)/server.o

client: $(CLIENT_BUILD)/client.o

library_admin: $(LIBRARY_ADMIN_BUILD)/library_admin.o

.PHONY: clean

# Regola generica per compilare i file .c
$(SERVER_BUILD)/server.o: $(wildcard $(SERVER_SRC)/*.c) $(wildcard $(DATABASE_SRC)/*.c) $(wildcard $(CONFIG_SRC)/*.c)
	mkdir -p $(SERVER_BUILD)
	$(CC) -o $@ $^ $(CFLAGS)

$(CLIENT_BUILD)/client.o: $(wildcard $(CLIENT_SRC)/*.c) $(wildcard $(CONFIG_SRC)/*.c)
	mkdir -p $(CLIENT_BUILD)
	$(CC) -o $@ $^ $(CFLAGS)

$(LIBRARY_ADMIN_BUILD)/library_admin.o: $(wildcard $(LIBRARY_ADMIN_SRC)/*.c) $(wildcard $(CONFIG_SRC)/*.c)
	mkdir -p $(LIBRARY_ADMIN_BUILD)
	$(CC) -o $@ $^ $(CFLAGS)


# Pulizia dei file compilati
clean:
	rm -rf $(SERVER_BUILD)/*
	rm -rf $(CLIENT_BUILD)/*
	rm -rf $(LIBRARY_ADMIN_BUILD)/*

clean_server:
	rm -rf $(SERVER_BUILD)/*

clean_client:
	rm -rf $(CLIENT_BUILD)/*

clean_library_admin:
	rm -rf $(LIBRARY_ADMIN_BUILD)/*

# Regola per avviare server.o
run_server: clean_server server
	$(SERVER_BUILD)/server.o

# Regola per avviare client.o
run_client: clean_client client
	$(CLIENT_BUILD)/client.o

# Regola per avviare library_admin.o
run_library_admin: clean_library_admin library_admin
	$(LIBRARY_ADMIN_BUILD)/library_admin.o