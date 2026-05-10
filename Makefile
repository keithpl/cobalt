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
