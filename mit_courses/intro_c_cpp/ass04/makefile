# ------------------------------ VARIABLES ------------------------------ #

# Compiler to use
COMPILER = gcc
# Flags for compiler
CFLAGS   = -Wall -pedantic -std=gnu99
# Define libraries to link into executable
# LIBS     = -lm
# Flags for debugging (combine multiple flags with spaces)
DFLAGS   = -D__DEBUG_EN -g
# Source files (only .c, no .h)
SOURCES_GEN = user.c bintree.c
# Output file
SOURCES_OUT = bintree

# ------------------------------ COMMANDS ------------------------------ #

# Build all ("make")
all: build

# Build application "make build"
build:
	$(COMPILER) $(SOURCES_GEN) $(CFLAGS) -o $(SOURCES_OUT)

# Build application with debugging info # "make debug"
debug:
	$(COMPILER) $(SOURCES_GEN) $(CFLAGS) $(DFLAGS) -o $(SOURCES_OUT)

# Remove generated files: "make clean"
clean:
	@if [ $(SOURCES_OUT) ] ; then rm -rf $(SOURCES_OUT) ; fi

