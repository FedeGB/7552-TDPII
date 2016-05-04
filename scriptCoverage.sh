#!/bin/sh

cd build-dir
lcov -c -i -d . -o .coverage.base
./tests
lcov -c -d . -o .coverage.run
lcov -d . -a .coverage.base -a .coverage.run -o .coverage.total
lcov --remove /home/juanma/Desktop/7552-TDPII/build-dir/.coverage.total '/home/juanma/Desktop/7552-TDPII/src/mongoose.c' '/usr/local/include/*' '4.8/*' '5/*' '/usr/include/*' 'include/gtest/*' 'src/json/json.h' -o .coverage.total
genhtml --no-branch-coverage -o . .coverage.total 
lcov --summary .coverage.total
