CORE = core/Image.cpp core/Image.h core/Pixel.cpp core/Pixel.h

SRC_TEST = $(CORE) test/main_test.cpp
FINAL_TARGET_TEST = test

SRC_AFFICHAGE = $(CORE) affichage/main_affichage.cpp
FINAL_TARGET_AFFICHAGE = affichage

INCLUDE_DIR_SDL = -I/usr/lib/x86_64-linux-gnu/
LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

CC = g++
LD = g++
LDFLAGS = 
CCFLAGS = -Wall -ggdb
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = -Isrc

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_AFFICHAGE) $(BIN_DIR)/$(FINAL_TARGET_TEST)

make_dir:
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)

$(BIN_DIR)/$(FINAL_TARGET_AFFICHAGE): $(SRC_AFFICHAGE:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)

$(BIN_DIR)/$(FINAL_TARGET_TEST): $(SRC_TEST:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR) $(LIBS_SDL) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_TEST) $(BIN_DIR)/$(FINAL_TARGET_AFFICHAGE)
