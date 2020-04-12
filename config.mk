NAME = marvin
VERSION = 1.0

# Customize below to fit your system

# paths
PREFIX = /usr

# libs
LIBS = -lncurses -lpanel

# flags
CFLAGS = -std=c99 -pedantic -Wall -Os
LDFLAGS = ${LIBS}

# compiler and linker
CC = cc

