# Do not use make's built-in implicit rules (-r) or built-in variables (-R).
# Disabling these built-ins avoids behavior that is difficult to debug and
# improves build performance.
MAKEFLAGS	+= -rR --warn-undefined-variables

SHELL		:= /usr/bin/env bash
.SHELLFLAGS	:= -eu -o pipefail -c

# If a rule's recipe exits with a non-zero status, automatically delete the
# target file.
.DELETE_ON_ERROR:
