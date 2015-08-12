rm *.gcno *.gcda *.gcov
make clean
make

./testBigNumber

gcov testBigNumber.cpp -r .
gcov bigNumber.cpp -r .
gcov bigNumber.h -r .
gcov bigNumber.hpp -r .

lcov -c -o big.info -d .
genhtml big.info -o big_result
firefox big_result/index.html



