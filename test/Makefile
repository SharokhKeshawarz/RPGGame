CC = gcc
SRC = test.c
CFLAGS = -I../CSFML/include
LDFLAGS = -L../CSFML/lib/gcc -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio -lcsfml-network

EXEC = game

all:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(EXEC)
	./$(EXEC)
