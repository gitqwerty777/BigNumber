# require gcov, lcov, genhtml and firefox

make clean
make

./testBigNumber

gcov ./src/testBigNumber.cpp -r .
gcov ./src/bigNumber.cpp -r .
gcov ./src/bigNumber.h -r .
gcov ./src/bigNumber.hpp -r .

lcov -c -o big.info -d .
genhtml big.info -o big_result
firefox big_result/index.html
