GCCVAL=g++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	GCCVAL=g++-7
endif

test:test.o
	$(GCCVAL) -std=c++14 -O3 -pthread --coverage test.o -o test -fopenmp
test.o:test.cpp FunctionalUtilities.h
	$(GCCVAL) -std=c++14 -O3 -pthread --coverage -c test.cpp -fopenmp
clean:
	-rm *.o *.out test