all: circumcenter

#declare variables
CC = g++
CFLAGS = -g3 -ggdb -Wall -Wextra
INCLUDE = ./include

BIN_DIR = ./bin
SRC_DIR = ./src

circumcenter: $(BIN_DIR) $(SRC_DIR)/circumcenter.cpp $(INCLUDE)/rational.h $(INCLUDE)/point.h $(INCLUDE)/line.h $(INCLUDE)/color.h
	$(CC) $(SRC_DIR)/circumcenter.cpp -I$(INCLUDE) $(CFLAGS) -o $(BIN_DIR)/circumcenter

clean:
	rm -f $(BIN_DIR)/*
