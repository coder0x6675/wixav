
BIN_DIR = bin
BLD_DIR = build
INC_DIR = include
SRC_DIR = source
TST_DIR = test
TARGET = wixav

VPATH = $(SRC_DIR) $(INC_DIR)

CC = clang++
CD = lldb
#CFLAGS = -I $(INC_DIR) -std=c++20 -march=native -Werror -Wall -Wextra -Wpedantic -g -Og
CFLAGS = -I $(INC_DIR) -std=c++20 -march=native -Werror -Wall -Wextra -Wpedantic -O3 -DNDEBUG


$(BIN_DIR)/$(TARGET): $(BLD_DIR)/main.o $(BLD_DIR)/common.o $(BLD_DIR)/Trie.o $(BLD_DIR)/Scanner.o $(BLD_DIR)/threadutil.o
	$(CC) $(CFLAGS) -o $@ $^

$(BLD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: test
test: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET) $(TST_DIR)/*

.PHONY: debug
debug: $(BIN_DIR)/$(TARGET)
	$(CD) ./$(BIN_DIR)/$(TARGET)

.PHONY: clean
clean:
	rm -f -- ./$(BIN_DIR)/* ./$(BLD_DIR)/*

