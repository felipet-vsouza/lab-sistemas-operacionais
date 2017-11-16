CC=gcc
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
DEBUG_FLAG=-g
LRT_FLAG=-lrt

all: main

main: $(SRC_DIR)/velha-main.c
	$(CC) -o $(BIN_DIR)/velha-main $(SRC_DIR)/velha-main.c $(LRT_FLAG)

clean:
	rm -rf $(BIN_DIR)