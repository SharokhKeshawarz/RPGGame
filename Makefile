CXX = g++
CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

LDLIBS = -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio -lcsfml-network -lm

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

EXEC := $(BUILD_DIR)/app

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS)  $^ -o $@ $(LDLIBS)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all clean rebuild
