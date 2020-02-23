# Declaring the variables.

CC=g++

CFLAGS=-c -e

SFMLINCLUDES=-Lsfml-hpp/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

ARCHIVESdotO=src/main.o src/jogo.o src/phrase.o src/sprites.o src/boat.o src/character.o src/gamedata.o

# Now executing the makefile.

all: executavel

executavel: $(ARCHIVESdotO)
	$(CC) $(ARCHIVESdotO) -o executavel $(SFMLINCLUDES)

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp $(SFMLINCLUDES)

jogo.o: src/jogo.cpp
	$(CC) $(CFLAGS) src/jogo.cpp $(SFMLINCLUDES)

phrase.o: src/phrase.cpp
	$(CC) $(CFLAGS) src/phrase.cpp $(SFMLINCLUDES)

sprites.o: src/sprites.cpp
	$(CC) $(CFLAGS) src/sprites.cpp $(SFMLINCLUDES)

boat.o: src/boat.cpp
	$(CC) $(CFLAGS) src/boat.cpp $(SFMLINCLUDES)

character.o: src/character.cpp
	$(CC) $(CFLAGS) src/character.cpp $(SFMLINCLUDES)

gamedata.o: src/gamedata.cpp
	$(CC) $(CFLAGS) src/gamedata.cpp $(SFMLINCLUDES)

clean:
	rm -rf *o executavel

open:
	code makefile src/main.cpp src/jogo.h src/jogo.cpp src/phrase.h src/phrase.cpp src/sprites.h src/sprites.cpp src/boat.h src/boat.cpp src/character.h src/character.cpp src/gamedata.h src/gamedata.cpp
