CPP=g++
CPPFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-ldpp

SRC_DIRS=src src/borothy
SRC_FILES=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
HEADERS=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.hpp))

OBJ_DIR=obj
OBJ_FILES=$(foreach dir, $(SRC_DIRS), \
  $(patsubst $(dir)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(dir)/*.cpp)))
BIN=borothy

define compile_dir
$(OBJ_DIR)/%.o: $(1)/%.cpp $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) -c $$< -o $$@
endef
$(foreach dir, $(SRC_DIRS), $(eval $(call compile_dir, $(dir))))

all: $(BIN)
$(BIN): $(OBJ_FILES) $(OBJ_DIR)
	$(CPP) $(OBJ_FILES) -o $@ $(LDFLAGS)

format: $(SRC_FILES) $(HEADERS)
	clang-format -i $(SRC_FILES) $(HEADERS) -style=file

$(OBJ_DIR):
	mkdir -p $@
clean:
	$(RM) -r $(OBJ_DIR) $(BIN)
