test:test.o
	g++ -std=c++14 -O3 -pthread --coverage test.o -o test -fopenmp
test.o:test.cpp
	g++ -std=c++14 -O3 -pthread --coverage -c test.cpp -fopenmp
clean:
	-rm *.o *.out test