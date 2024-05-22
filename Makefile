# Eliminate the use of make's built-in implicit rules (-r) and built-in
# variables (-R). This avoids behavior that is difficult to debug and improves
# performance. Also, give a warning when an undefined variable is referenced.
MAKEFLAGS	+= -rR --warn-undefined-variables

# Set the shell to bash and configure it to exit on error, treat unset
# variables as errors, and ensure that any failure in a pipline causes the
# entire pipeline to fail.
SHELL		:= bash
.SHELLFLAGS	:= -eu -o pipefail -c

# Automatically delete target files if the rule's commands exit with a non-zero
# status.
.DELETE_ON_ERROR:

CC		:= gcc
CFLAGS		:= -std=c17 -pipe
RELEASE_CFLAGS	:= -O2 -march=native -flto=auto -DNDEBUG
DEBUG_CFLAGS	:= -Og -g3 -DDEBUG -Werror
SANITIZE_CFLAGS	:= -fsanitize=address,leak,undefined

WARNS		:= -Wall -Wextra -pedantic -pedantic-errors -Wformat=2	\
		   -Wshadow -Wstrict-prototypes -Wstrict-overflow=2	\
		   -Wvla -Wredundant-decls -Wnested-externs -Wcast-qual	\
		   -Wfloat-equal -Wdouble-promotion -Wpointer-arith	\
		   -Wundef -Winit-self -Wwrite-strings -Wconversion

GCC_WARNS	:= -Wjump-misses-init -Wlogical-op -Walloc-zero

ifeq ($(CC),gcc)
	WARNS += $(GCC_WARNS)
endif

# Additional CFLAGS for the C language server, unrelated to compilation or
# assembly.
LSP_CFLAGS	:= $(CFLAGS) $(RELEASE_CFLAGS) $(WARNS)			\
		   -Wreserved-identifier -Wno-unused-function		\
		   -Wno-empty-translation-unit

LSP_CFLAGS_FILE	:= compile_flags.txt

LDFLAGS		:= -Wl,-O1,--sort-common,--as-needed
LDLIBS		:=
INCLUDES	:= -I ./include

SRC_DIR		:= ./src
BUILD_DIR	:= ./build
SOURCES		:= $(wildcard $(SRC_DIR)/*.c)
OBJECTS		:= $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET_DIR	:= ./bin
TARGET_NAME	:= cobalt
TARGET		:= $(TARGET_DIR)/$(TARGET_NAME)

.PHONY: all
all: release

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(TARGET_DIR)
	@rm -f gmon.out .clangd ~*

.PHONY: debug
debug: CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS) $(WARNS)
debug: $(TARGET)

.PHONY: sanitize
sanitize: CFLAGS := $(CFLAGS) $(DEBUG_CFLAGS) $(SANITIZE_CFLAGS) $(WARNS)
sanitize: $(TARGET)

.PHONY: release
release: CFLAGS := $(CFLAGS) $(RELEASE_CFLAGS) $(WARNS)
release: $(TARGET)

$(TARGET): $(TARGET_DIR)
$(TARGET): $(LSP_CFLAGS_FILE)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(INCLUDES) $(OBJECTS) -o $@

$(OBJECTS): $(BUILD_DIR)
$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET_DIR):
	@mkdir -p $@

$(BUILD_DIR):
	@mkdir -p $@

$(LSP_CFLAGS_FILE):
	@echo "$(LSP_CFLAGS) $(INCLUDES)" | xargs -n 1 > $@
