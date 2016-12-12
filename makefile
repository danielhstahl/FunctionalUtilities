test:test.o
	g++ -std=c++14 -O3 -pthread test.o -o test -fopenmp
test.o:test.cpp
	g++ -std=c++14 -O3 -pthread -c test.cpp -fopenmp
clean:
	-rm *.o *.out test