# Do not use make's built-in implicit rules (-r) or built-in variables (-R).
# Disabling these built-ins avoids behavior that is difficult to debug and
# improves build performance.
MAKEFLAGS	+= -rR --warn-undefined-variables

SHELL		:= /bin/bash
.SHELLFLAGS	:= -eu -o pipefail -c

# Delete the target file if the recipe fails.
.DELETE_ON_ERROR:

# GCC is the default toolchain; Clang is also supported and tested.
CC		:= gcc

CFLAGS		:= -std=c17 -pipe -pthread -D_POSIX_C_SOURCE=200809L

RELEASE_CFLAGS	:= -march=native -O2 -flto=auto -DNDEBUG
DEBUG_CFLAGS	:= -Og -g3 -fno-omit-frame-pointer -DDEBUG
SANITIZE_CFLAGS	:= -fsanitize=address,leak,undefined -fno-sanitize-recover=all

WARNS		:= -Wall -Wextra -Wpedantic -pedantic-errors -Wformat=2	\
		   -Wshadow -Wstrict-prototypes -Wstrict-overflow=2	\
		   -Wvla -Wredundant-decls -Wnested-externs -Wcast-qual	\
		   -Wfloat-equal -Wdouble-promotion -Wpointer-arith	\
		   -Wundef -Winit-self -Wwrite-strings -Wconversion	\
		   -Wmissing-prototypes -Wmissing-declarations -Walloca	\
		   -Wnull-dereference -Wcast-align

DEBUG_WARNS	:= -Werror

# Additional warnings that may not be supported by all compilers, but are
# supported by GCC.
GCC_WARNS	:= -Wjump-misses-init -Wlogical-op -Walloc-zero		\
		   -Wduplicated-branches -Wduplicated-cond

CC_VERSION_TEXT	:= $(shell $(CC) --version 2>/dev/null | head -n 1)

ifneq ($(findstring gcc,$(CC_VERSION_TEXT)),)
    WARNS += $(GCC_WARNS)
endif

# Additional CFLAGS and warnings defined only for the C language server,
# unrelated to the final build of the project.
LSP_CFLAGS	:= $(CFLAGS) $(RELEASE_CFLAGS) $(WARNS)			\
		   -Wreserved-identifier -Wno-unused-function		\
		   -Wno-empty-translation-unit

LSP_CFLAGS_FILE	:= compile_flags.txt

DEPFLAGS	:= -MMD -MP
LDFLAGS		:= -pthread -Wl,-O1,--sort-common,--as-needed,--fatal-warnings
LDLIBS		:=
INCLUDES	:= -I./include

SRC_DIR		:= ./src
OBJ_DIR		:= ./obj
BUILD_DIR	:= ./build

SOURCES		:= $(wildcard $(SRC_DIR)/*.c)
OBJECTS		:= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJECTS:.o=.d)

TARGET_NAME	:= cobalt
TARGET		:= $(BUILD_DIR)/$(TARGET_NAME)
