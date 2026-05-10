# Do not use make's built-in implicit rules (-r) or built-in variables (-R).
# Disabling these built-ins avoids behavior that is difficult to debug and
# improves build performance.
MAKEFLAGS	+= -rR --warn-undefined-variables

SHELL		:= /usr/bin/env bash
.SHELLFLAGS	:= -eu -o pipefail -c

# If a rule's recipe exits with a non-zero status, automatically delete the
# target file.
.DELETE_ON_ERROR:

# The default toolchain is GCC; however, Clang is also supported and tested.
CC		:= gcc

CPPFLAGS	:= -D_POSIX_C_SOURCE=200809L -I./include

CFLAGS		:= -std=c17 -pipe -pthread
RELEASE_CFLAGS	:= -march=native -O2 -flto=auto -DNDEBUG
DEBUG_CFLAGS	:= -Og -g3 -fno-omit-frame-pointer -DDEBUG
ASAN_CFLAGS	:= -fsanitize=address,leak,undefined -fno-sanitize-recover=all

LDFLAGS		:= -Wl,--sort-common,--as-needed
RELEASE_LDFLAGS	:= -Wl,-O1
DEBUG_LDFLAGS	:= -Wl,--fatal-warnings
LDLIBS		:=

WARNS		:= -Wall -Wextra -Wpedantic -pedantic-errors -Wformat=2	\
		   -Wshadow -Wstrict-prototypes -Wstrict-overflow=2	\
		   -Wredundant-decls -Wnested-externs -Wcast-qual	\
		   -Wfloat-equal -Wdouble-promotion -Wpointer-arith	\
		   -Wundef -Winit-self -Wwrite-strings -Wconversion	\
		   -Wmissing-prototypes -Wmissing-declarations -Wvla	\
		   -Walloca -Wnull-dereference -Wcast-align

DEBUG_WARNS	:= -Werror

# Additional warnings that may not be supported by all compilers, but are
# supported by GCC.
GCC_WARNS	:= -Wjump-misses-init -Wlogical-op -Walloc-zero		\
		   -Wduplicated-branches -Wduplicated-cond

# Detect the compiler from its `$(CC) --version` output rather than parsing
# $(CC), which may be a symlink, alias, or cross-compiler prefix.
CC_VERSION_TEXT	:= $(shell LC_ALL=C $(CC) --version 2>/dev/null | head -n 1)

ifneq ($(findstring gcc,$(CC_VERSION_TEXT)),)
    WARNS += $(GCC_WARNS)
endif

# Additional CFLAGS and warnings defined only for the language server, clangd,
# unrelated to the final build of the project.
LSP_CFLAGS	:= $(CFLAGS) $(RELEASE_CFLAGS) $(WARNS)			\
		   -Wreserved-identifier -Wno-unused-function		\
		   -Wno-empty-translation-unit

LSP_CFLAGS_FILE	:= compile_flags.txt

DEPFLAGS	:= -MMD -MP

SRC_DIR		:= ./src
OBJ_DIR		:= ./obj
BUILD_DIR	:= ./build

SOURCES		:= $(wildcard $(SRC_DIR)/*.c)
OBJECTS		:= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJECTS:.o=.d)

TARGET_NAME	:= cobalt
TARGET		:= $(BUILD_DIR)/$(TARGET_NAME)
