all: circumcenter

#declare variables
CC = g++
CFLAGS = -g3 -ggdb -Wall -Wextra
INCLUDE = ./src

BIN_DIR = ./bin
SRC_DIR = ./src

circumcenter: $(BIN_DIR) $(SRC_DIR)/circumcenter.cpp $(SRC_DIR)/rational.h $(SRC_DIR)/point.h $(SRC_DIR)/line.h
	$(CC) $(SRC_DIR)/circumcenter.cpp -I$(INCLUDE) $(CFLAGS) -o $(BIN_DIR)/circumcenter

clean:
	rm -f $(BIN_DIR)/*