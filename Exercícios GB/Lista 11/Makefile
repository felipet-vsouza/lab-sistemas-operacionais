CC=gcc
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
DEBUG_FLAG=-g

all: main

main: $(SRC_DIR)/jogo-da-velha.c $(INC_DIR)/velha-lib.c
	$(CC) -o $(BIN_DIR)/jogo-da-velha $(SRC_DIR)/jogo-da-velha.c $(INC_DIR)/velha-lib.c