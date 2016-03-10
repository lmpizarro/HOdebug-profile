.PHONY: default help object executable all clean
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_C = $(patsubst %.c, %_c.o, $(SOURCE_C))

EXECUTABLE = test_oob2.e

#CFLAGS = -DDEBUG

default: help

help:
	@echo "\
Options:\n\n\
  make objects:       compiler makes objects for every *.c and *.f90\n\
  make executable:    compiler makes executable\n\
  make all:           build all previous\n\
  make clean:         delete output files\n\
  make help:          display this help"

objects: $(OBJECTS_C)

executable: $(EXECUTABLE)

all: objects executable

%_c.o: %.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(IFLAGS)

test_oob2.e: test_oob2_c.o 
	$(LD) $^ -o $@  $(LFLAGS)


clean:
	rm -rfv $(OBJECTS_C) $(EXECUTABLE)
