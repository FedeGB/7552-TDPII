#!/bin/bash

git clone -b registerAndLogin https://github.com/bliberini/7552-TDPII
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

lcov --no-external --capture --initial --directory /7552-TDPII/build-dir/ --output-file /7552-TDPII/build-dir/proy_base.info
./tests
lcov --capture --directory /7552-TDPII/build-dir/ --output-file /7552-TDPII/build-dir/proy_tests.info
lcov --add-tracefile /7552-TDPII/build-dir/proy_base.info --add-tracefile /7552-TDPII/build-dir/proy_tests.info  --output-file /7552-TDPII/build-dir/proy_total.info
lcov --remove /7552-TDPII/build-dir/proy_tests.info '/usr/include/' '/usr/lib/*' '/7552-TDPII/src/mongoose.c' '/usr/local/include/*' '4.8/*' 'src/json/json.h' 'include/gtest/*' -o /7552-TDPII/build-dir/proy_tests.info
