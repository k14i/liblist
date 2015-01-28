SUBDIRS = lib

bin_PROGRAMS = example

example_LDFLAGS = -L./lib
example_LDADD = -llist

example_CFLAGS = -I ./lib

example_DEPENDENCIES = ./lib/liblist.la

example_SOURCES = example.c
#example_LDADD = ./lib/liblist.la

AM_CFLAGS = -Wall
