CFLAGS=--coverage -g

main: testBigNumber manualTestBigNumber

testBigNumber: bigNumber.o testBigNumber.o
	g++ $(CFLAGS) bigNumber.o testBigNumber.o -o testBigNumber
manualTestBigNumber: bigNumber.o manualTestBigNumber.o
	g++ $(CFLAGS) bigNumber.o manualTestBigNumber.o -o manualTestBigNumber

bigNumber.o: bigNumber.cpp bigNumber.h bigNumber.hpp
	g++ $(CFLAGS) bigNumber.cpp -c
testBigNumber.o: testBigNumber.cpp bigNumber.h bigNumber.hpp
	g++ $(CFLAGS) testBigNumber.cpp -c
manualTestBigNumber.o: manualTestBigNumber.cpp bigNumber.h bigNumber.hpp
	g++ $(CFLAGS) manualTestBigNumber.cpp -c
clean:
	rm -rf *.o; rm testBigNumber; rm manualTestBigNumber
