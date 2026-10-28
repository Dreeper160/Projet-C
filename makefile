CC = gcc

# Directories


SRC_DIR = src
BUILD_DIR = build



TARGET = $(BUILD_DIR)/Bomberman
# Compilation flags
CFLAGS =  -std=c89 -Wall -Wextra -D_POSIX_C_SOURCE=199309L

# Libraries
LDLIBS = -lMLV -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -lSDL_mixer -lxml2 -lglib-2.0

# Automatic retrieval of source files (I hate make)
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Main target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
# Create the build directory
$(BUILD_DIR):
	mkdir -p "$(BUILD_DIR)"
# Clean up build files
clean:
	rm -rf "$(BUILD_DIR)"

# Complete recompilation
re: clean all

.PHONY: all clean re
