# Declaring the variables.

CC=g++

CFLAGS=-c

SFMLINCLUDES=-L../sfml-hpp/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Now executing the makefile.

all: executavel

executavel: main.o jogo.o auxiliares.o
	$(CC) main.o jogo.o auxiliares.o -o executavel $(SFMLINCLUDES)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp $(SFMLINCLUDES)

jogo.o: jogo.cpp
	$(CC) $(CFLAGS) jogo.cpp $(SFMLINCLUDES)

auxiliares.o: auxiliares.cpp
	$(CC) $(CFLAGS) auxiliares.cpp $(SFMLINCLUDES)

clean:
	rm -rf *o executavel
