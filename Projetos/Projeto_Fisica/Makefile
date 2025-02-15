## Descomentar/alterar de acordo com o projeto


MVC=fisica.c


## Não alterar a partir daqui

CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99 
# CFLAGS+=-Werror -pedantic

main: fisica.c $(UTILS) $(MVC)
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$@ $^ -lm
