CC = gcc -c
CURSES = -lncurses
CFLAGS = -W -Wall

all: run

run: Yahtzee clean

Yahtzee: main.o Partie.o Score.o Regles.o Chargement.o Lancer.o Highscore.o Affichage.o Initialisation.o Fenetre.o
	gcc -o $@ $^ $(CURSES) $(CFLAGS) -lm

main.o: ./Sources/main.c ./include/Global.h 
	$(CC) $^ $(CURSES) $(CFLAGS) 

Score.o: ./Sources/Score.c ./include/Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)

Regles.o: ./Sources/Regles.c ./include/Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)

Chargement.o: ./Sources/Chargement.c ./include/Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)

Lancer.o: ./Sources/Lancer.c ./include/Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)

Highscore.o: ./Sources/Highscore.c ./include/Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)

Affichage.o: ./Sources/Affichage.c ./include/Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)
	
Initialisation.o: ./Sources/Initialisation.c ./include/Global.h 
	$(CC) $^ $(CURSES) $(CFLAGS)

Fenetre.o: ./Sources/Fenetre.c ./include/Global.h 
	$(CC) $^ $(CURSES) $(CFLAGS)

Partie.o: ./Sources/Partie.c ./include/Global.h 
	$(CC) $^ $(CURSES) $(CFLAGS)

clean: 
	rm -rf *.~ *.o 


