all: bignumber

bignumber: 
	cd src; make; cp manualTestBigNumber testBigNumber ..

clean:
	cd src; make clean; rm *.gcno *.gcda *.gcov; cd ../; rm *.gcno *.gcda *.gcov
