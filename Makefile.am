#CC=/usr/local/bin/gcc-4.9
#CFLAGS=-Wall
#LDFLAGS=-lm
#
#AUTOMAKE_OPTIONS = foreign
#AC_CONFIG_AUX_DIR = ./config/aux
##AC_CANONICAL_TARGET
SUBDIRS = src
#EXTRA_DIST = autogen.sh
#INCLUDE = -I./src/lib #-I./src/include
#TARGET = ./bin/$(shell basename `readlink -f .`)
#OBJDIR = ./tmp/.obj
DIST_SUBDIRS = $(SUBDIRS)

# NOTE: 
#   libtoolize: Consider adding `-I m4' to ACLOCAL_AMFLAGS in Makefile.am.
ACLOCAL_AMFLAGS = -I m4


#OBJS: liblist.la example.o
#
#example: $(OBJS)
#	g++ -o example $(OBJS)
#
#liblist.a: liblist.o
#	ar r $@ $<
#	ranlib $@
#
#.o:
#	g++ -c $< -g -O2
#
#all: example
#
#clean:
#	\rm -rf *.o *.a example

#all: clean $(TARGET)
#clean: distclean
#       find . -name Makefile.in -exec \rm -f {} \;
#       find . -name Makefile -exec \rm -f {} \;

#OBJECTS=./src/lib/list.o
#SOURCE=example.c
#target: $(OBJECTS)
#	    $(CC) $(CFLAGS) $(OBJECTS) -o target $(LDFLAGS)

