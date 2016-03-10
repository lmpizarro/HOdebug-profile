.PHONY: default help object executable all clean
CC = gcc

LD = $(CC)

SOURCE_C = $(wildcard *.c)
OBJECTS_C = $(patsubst %.c, %_c.o, $(SOURCE_C))

EXECUTABLE = test_fpe1.e

CFLAGS = -DTRAPFPE
IFLAGS = -I./fpe_x87_sse
LFLAGS = ./fpe_x87_sse/fpe_x87_sse_c.o -lm

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

test_fpe1.e: test_fpe1_c.o 
	$(LD) $^ -o $@  $(LFLAGS)

test_fpe2.e: test_fpe2_c.o 
	$(LD) $^ -o $@  $(LFLAGS)

clean:
	rm -rfv $(OBJECTS_C) $(EXECUTABLE)
