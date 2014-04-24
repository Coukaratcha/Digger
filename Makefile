.PHONY: clean, mrproper
.SUFFIXES:

CC = gcc
EXEC = Digger
DEBUG = yes
CFLAGS = -Wall `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)
HEADERS= $(wildcard include/*.h)
# création de l'exécutable 'Programme'
all: $(EXEC)

$(EXEC): $(OBJ)
		$(CC) $(LDFLAGS) -o bin/$@ $^

main.o: $(HEADERS)

%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

# suppression des fichiers temporaires
clean:
		rm -rf src/*.o

# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
		rm -rf bin/$(EXEC)

# test des fuites mémoires avec valgrind
valgrind: $(EXEC)
		valgring bin/$@