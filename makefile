main: bigNumber.o testBigNumber.o
	g++   bigNumber.o testBigNumber.o -o bignumber
bigNumber.o: bigNumber.cpp bigNumber.h bigNumber.hpp
	g++ bigNumber.cpp -c
testBigNumber.o: testBigNumber.cpp bigNumber.h bigNumber.hpp
	g++ testBigNumber.cpp -c
clean:
	rm -rf *.o
