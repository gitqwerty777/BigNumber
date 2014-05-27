main: test_bignumber.o
	  g++ test_bignumber.c -o a
test_bignumber.o: test_bignumber.c
				  g++ test_bignumber.c -c 
clean:
	rm -rf test_bignumber.o	