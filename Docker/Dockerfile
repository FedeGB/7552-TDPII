# Usamos de imagen base a Debian
FROM ubuntu


# Instalar dependecias de rocksdb
RUN apt-get update
RUN apt-get -f install
RUN apt-get -y install wget
RUN apt-get -y install make
RUN apt-get -y install build-essential g++
RUN apt-get -y install git-core
RUN apt-get -y install cmake
RUN apt-get install -y libgflags-dev
RUN apt-get install -y libsnappy-dev
RUN apt-get install -y libbz2-dev 
RUN apt-get install -y zlib1g-dev
RUN apt-get install -y unzip
RUN apt-get install -y lcov
RUN apt-get install -y curl
RUN apt-get install -y debhelper cmake bison flex libgtk2.0-dev libltdl3-dev libncurses-dev libnet1-dev libpcap-dev libpcre3-dev libssl-dev libcurl4-openssl-dev ghostscript


#Jsoncpp
RUN wget https://github.com/open-source-parsers/jsoncpp/archive/master.zip && unzip master.zip && cd jsoncpp-master/ && mkdir -p build/debug && cd build/debug/ &&     cmake -DCMAKE_BUILD_TYPE=debug -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G          "Unix Makefiles" ../.. && make && cd src/lib_json/ && cd

# Gtests
RUN wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz && tar xf release-1.7.0.tar.gz && cd googletest-release-1.7.0 && cmake -DBUILD_SHARED_LIBS=ON . && make && cp -a include/gtest /usr/include && cp -a libgtest_main.so libgtest.so /usr/lib/ && cd -
#RUN ldconfig

# Rocksdb
RUN wget https://github.com/facebook/rocksdb/archive/v4.3.1.tar.gz -O rocksdb.tar.gz && tar xfv rocksdb.tar.gz && cd rocksdb* && make shared_lib && make install-static && cd -

# Copiamos entry-point.sh
COPY docker-entrypoint.sh /

# El entry point lo que hace es git clone
ENTRYPOINT ["./docker-entrypoint.sh"]


# Ejecuta compilacion y test
CMD 
