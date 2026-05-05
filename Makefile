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
ASAN_CFLAGS	:= -fsanitize=address,leak,undefined -fno-sanitize-recover=all

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

CC_VERSION_TEXT	:= $(shell LC_ALL=C $(CC) --version 2>/dev/null | head -n 1)

ifneq ($(findstring gcc,$(CC_VERSION_TEXT)),)
    WARNS += $(GCC_WARNS)
endif
