CC = gcc -c
CURSES = -lncurses
CFLAGS = -W -Wall

test: test_CalculScore.o Score.o 
	gcc -o $@ $^ $(CURSES) $(CFLAGS) -lm

test_CalculScore.o: test_CalculScore.c Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)

Score.o: Score.c Global.h
	$(CC) $^ $(CURSES) $(CFLAGS)



