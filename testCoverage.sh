rm *.gcno *.gcda *.gcov
make clean
make

./bignumber

gcov testBigNumber.cpp
gcov bigNumber.cpp
gcov bigNumber.h
gcov bigNumber.hpp

lcov -c -o big.info -d .
genhtml big.info -o big_result
firefox big_result/index.html



