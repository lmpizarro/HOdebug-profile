.PHONY: default help object executable all clean
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_C = $(patsubst %.c, %_c.o, $(SOURCE_C))

EXECUTABLE = profile_me_1.e profile_me_2.e

CFLAGS = -pg

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
	$(CC) -c $^ -o $@ $(CFLAGS)

profile_me_1.e: profile_me_1.o 
	$(LD) $^ -o $@ -pg

profile_me_2.e: profile_me_2.o 
	$(LD) $^ -o $@ -lm -pg

clean:
	rm -rfv *.o $(EXECUTABLE)
