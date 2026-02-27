TARGET = yellow
BUILD_DIR = .build
SRC_DIR = src
CC ?= gcc
CFLAGS_BASE = -std=c99 $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer)
CFLAGS_DEV = -O0 -Wall -Wextra -Werror -Wpedantic -fsanitize=address -g -fsanitize-address-use-after-scope
CFLAGS_RELEASE = -O2
LDLIBS_BASE = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer)
LDLIBS_DEV = -fsanitize=address -g -fsanitize-address-use-after-scope
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS ?= $(CFLAGS_BASE) $(CFLAGS_DEV)
LDLIBS ?= $(LDLIBS_BASE) $(LDLIBS_DEV)
$(BUILD_DIR):
	mkdir $(BUILD_DIR)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(TARGET): $(OBJS)
	$(CC) $^  -o $@ $(LDLIBS)

.PHONY: all clean run rebuild release

all: $(TARGET)
clean:
	$(RM) -r $(TARGET) $(BUILD_DIR)
run: $(TARGET)
	./$<
rebuild: clean all
release: CFLAGS = $(CFLAGS_BASE) $(CFLAGS_RELEASE)
release: LDLIBS = $(LDLIBS_BASE)
release: all
