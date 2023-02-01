# gcc >= 11; zB in 
#CC=/opt/sw/gcc/11.2.0/bin/g++
CC=g++
CFLAGS=-g -Wall -std=c++17
LDFLAGS=-lboost_iostreams -lboost_filesystem -lboost_system
#LDFLAGS=-lboost_iostreams  -lboost_system // enough for example_simple
#OBJ= 

all: example-misc example_simple 

example-misc: example-misc.o
	@echo Linking $@
	$(CC) $(LDFLAGS) -o example-misc example-misc.o

example_simple: example_simple.o
	@echo Linking $@
	$(CC) $(LDFLAGS) -o example_simple example_simple.o


%.o: %.cpp gnuplot-iostream.h
	@echo Compiling $@ 	
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	rm -r example-misc example_simple *.o
