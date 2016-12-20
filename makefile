test:test.o
	#g++ -std=c++14 -O3 -pthread test.o -o test -fopenmp
	clang -std=c++14 -stdlib=libstdc++ -O3 -pthread test.o -o test -fopenmp=libiomp5 
test.o:test.cpp
	#g++ -std=c++14 -O3 -pthread -c test.cpp -fopenmp
	clang -std=c++14 -stdlib=libstdc++ -O3 -pthread -c test.cpp -fopenmp=libiomp5 
clean:
	-rm *.o *.out test