OBJ_DIR = obj
SRC_DIR1 = .
SRC_DIR2 = controller
SRC_DIR3 = core
SRC_DIR4 = model
SRC_DIR5 = utils
SRC_DIR6 = view
SRC = $(wildcard $(SRC_DIR1)/*.cpp) $(wildcard $(SRC_DIR2)/*.cpp) $(wildcard $(SRC_DIR3)/*.cpp) $(wildcard $(SRC_DIR4)/*.cpp) $(wildcard $(SRC_DIR5)/*.cpp) $(wildcard $(SRC_DIR6)/*.cpp)
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
VPATH=.:controller:core:model:utils:view


RELEASE_DIR = bin
RELEASE_DEBUG_DIR = binDebug
EXEC =$(RELEASE_DIR)/sfml_test
EXEC_DEBUG =$(RELEASE_DEBUG_DIR)/sfml_test


CC = g++
CFLAGS = -Wall -Werror -O1 -std=c++11
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS_DEBUG = -g


all: createDir $(EXEC)

makeDebug: $(EXEC_DEBUG)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC_DEBUG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDFLAGS_DEBUG)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

createDir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(RELEASE_DEBUG_DIR)

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(RELEASE_DEBUG_DIR)
