## Blueprint Makefile
SRC_FILES := sdltest
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

## create vars for target, src and object files
EXE := $(BIN_DIR)/a.out
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))


BREW_PREFIX := /opt/homebrew/Cellar
SDL3_PREFIX := $(BREW_PREFIX)/sdl3/3.2.2
SDL2_PREFIX := $(BREW_PREFIX)/sdl2/2.30.12
FFMPEG_PREFIX := $(BREW_PREFIX)/ffmpeg/7.1_4

SDL3_CFLAGS := -I$(SDL3_PREFIX)/include -I$(SDL3_PREFIX)/include
SDL3_LDFLAGS := -L$(SDL3_PREFIX)/lib -lsdl3 -L$(SDL3_PREFIX)/lib -lsdl3_image
SDL2_CFLAGS := -I$(SDL2_PREFIX)/include -I$(SDL2_PREFIX)/include
SDL2_LDFLAGS := -L$(SDL2_PREFIX)/lib -lsdl2 -L$(SDL2_PREFIX)/lib -lsdl2_image
FFMPEG_CFLAGS := -I$(FFMPEG_PREFIX)/include
FFMPEG_LDFLAGS := -I$(FFMPEG_PREFIX)/lib -lavcodec

## for debugging
CFLAGS := -fsanitize=address -fsanitize=undefined -Wall -Wextra -g -MMD -MP $(SDL3_CFLAGS) $(FFMPEG_CFLAGS)
LDFLAGS := -fsanitize=address -fsanitize=undefined $(SDL3_LDFLAGS) $(FFMPEG_LDFLAGS)

## for normal comp
# CFLAGS := -Wall -Wextra -g -MMD -MP
# LDFLAGS :=

## select compiler
# CC := gcc-14
CC := clang


## Targets
# Phony targets aren't treated as files
.PHONY: all run clean

# Default target, executed with 'make' command
build: $(EXE)

# Execute immediatelly after building
run: $(EXE)
	./bin/a.out

# Link all the objectfiles into an exe
$(EXE): $(OBJ) | $(BIN_DIR) # 
	$(CC) $(LDFLAGS) $^ -o $@
	dsymutil $@

# Only source files that have been changed get rebuilt
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean for rebuilt - Using implicit variable RM (rm -f)
clean:
	@$(RM) -r $(OBJ_DIR) $(BIN_DIR)

upclang:
    echo "CompileFlags:" > .clangd
    echo "  Add:" >> .clangd
    echo "    - $(SDL3_CFLAGS) $(SDL2_CFLAGS) $(FFMPEG_CFLAGS)" >> .clangd

# Make sure directories exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# check header files for changes
-include $(OBJ:.o=.d)



### Helper Legend ###
# normal-prerequisites | order-only-prerequisites (no out of date check)

### Automatic variables:
# $^: all prerequisites
# $<: first prerequisite
# $@: target

### Specifics
# -MDD, -MP: create .d files for header deps
# -g: additional debug info gets created
# dsymutil: extract debug info into seperate file, Mac thing I think..
