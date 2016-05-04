#!/bin/bash

git clone https://github.com/bliberini/7552-TDPII
echo `ls`
cd 7552-TDPII
mkdir build-dir
cd build-dir
cd 
cd ..
cd jsoncpp-master/build/debug/src/lib_json/
cp -a libjsoncpp.a /7552-TDPII/lib/
cd -
cd 7552-TDPII/build-dir
cmake ..
make
cd ..
sh scriptCoverage.sh