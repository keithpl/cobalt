# Do not use make's built-in implicit rules (-r) or built-in variables (-R).
# Disabling these built-ins avoids behavior that is difficult to debug and
# improves build performance.
MAKEFLAGS	+= -rR --warn-undefined-variables

SHELL		:= /bin/bash
.SHELLFLAGS	:= -eu -o pipefail -c

# Delete the target file if the recipe fails.
.DELETE_ON_ERROR:
