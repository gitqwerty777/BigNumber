CFLAGS=--coverage -g

main: bigNumber.o testBigNumber.o
	g++ $(CFLAGS) bigNumber.o testBigNumber.o -o bignumber
bigNumber.o: bigNumber.cpp bigNumber.h bigNumber.hpp
	g++ $(CFLAGS) bigNumber.cpp -c
testBigNumber.o: testBigNumber.cpp bigNumber.h bigNumber.hpp
	g++ $(CFLAGS) testBigNumber.cpp -c
clean:
	rm -rf *.o
