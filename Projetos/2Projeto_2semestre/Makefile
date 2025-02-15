## Descomentar/alterar de acordo com o projeto

UTILS=src/utils/singly_linked_list.c
UTILS+=src/utils/open_hash_table.c

MVC=src/views/cli.c
MVC+=src/controllers/App.c
MVC+=src/models/app_components.c

## Não alterar a partir daqui

CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99 
# CFLAGS+=-Werror -pedantic

main: src/main.c $(UTILS) $(MVC)
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$@ $^ -lm
