main: testBigNumber.o
	g++ testBigNumber.o -o bignumber
testBigNumber.o: testBigNumber.cpp bigNumber.h
	g++ testBigNumber.cpp -c 
clean:
	rm -rf *.o
