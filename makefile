CC = g++
SRC_DIR = ./src
SRC_FILE = $(shell find $(SRC_DIR) -name "*.cc")
# SRC_FILE += $(shell find $(SRC_DIR) -name "*.h")
TURING = turing
OUT_DIR = ./build

$(TURING): $(SRC_FILE)
	mkdir -p $(OUT_DIR)
	$(CC) $(SRC_FILE) -o $(OUT_DIR)/$(TURING)

debug:$(SRC_FILE)
	mkdir -p $(OUT_DIR)
	$(CC) $(SRC_FILE) -o $(OUT_DIR)/$(TURING)_g -g

clean:
	rm $(OUT_DIR) -r