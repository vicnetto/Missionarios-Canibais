# Declaring the variables.

CC=g++

CFLAGS=-c -e

SFMLINCLUDES=-Lsfml-hpp/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Now executing the makefile.

all: executavel

executavel: src/main.o src/jogo.o src/auxiliares.o
	$(CC) src/main.o src/jogo.o src/auxiliares.o -o executavel $(SFMLINCLUDES)

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp $(SFMLINCLUDES)

jogo.o: src/jogo.cpp
	$(CC) $(CFLAGS) src/jogo.cpp $(SFMLINCLUDES)

auxiliares.o: src/auxiliares.cpp
	$(CC) $(CFLAGS) src/auxiliares.cpp $(SFMLINCLUDES)

clean:
	rm -rf *o executavel

open:
	code makefile src/main.cpp src/jogo.h src/jogo.cpp src/auxiliares.h src/auxiliares.cpp
