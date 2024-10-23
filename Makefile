CC = gcc
CFLAGS = -ICSFML/include -Iinclude
LDFLAGS = -LCSFML/lib/gcc -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio -lcsfml-network

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))
EXEC = game

all: $(EXEC)
	./$(EXEC)

# Compile each .c file into .o file inside bin/
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files to create the final executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

clean:
	rm -rf bin/*.o $(EXEC)
