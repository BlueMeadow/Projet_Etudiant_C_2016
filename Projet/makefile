CURSES = -lncurses

CFLAGS = -W -Wall


CC = gcc -c

all: run

run: Yahtzee clean

Yahtzee: main.o Affichage.o Chargement.o Fenetre.o Highscore.o Initialisation.o Lancer.o Partie.o Regles.o Score.o
	gcc -o $@ $^ $(CURSES) $(CFLAGS)

main.o: ./Sources/main.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Affichage.o: ./Sources/Affichage.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Chargement.o: ./Sources/Chargement.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Fenetre.o: ./Sources/Fenetre.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Highscore.o: ./Sources/Highscore.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Initialisation.o: ./Sources/Initialisation.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Lancer.o: ./Sources/Lancer.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Partie.o: ./Sources/Partie.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Regles.o: ./Sources/Regles.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

Score.o: ./Sources/Score.c ./lib/Global.h
	$(CC) $^ -g $(CURSES) $(CFLAGS)

clean: 
	rm -rf *.~ *.o 
