# 7552-TDPII
Grupo de Taller de Programación II

Guia de instalacion del ambiente:

1- Instalar CMake
	- sudo apt-get install cmake

2 - Instalación de RocksDB

	- Descargar el ultimo release de: https://github.com/facebook/rocksdb/archive/master.zip

	- Descomprimir el archivo "rocksdb-master.zip"

	- Ingresar a la carpeta "rocksdb-master" en una terminal

	- Ingresar como sudo su

	- Ejecutar los sig comandos:

		- make all

		- make install

Instalar las siguientes librerias tambien:

	apt-get install libgflags-dev

	apt-get install libsnappy-dev

	apt-get install zlib1g-dev

	apt-get install libbz2-dev


3 - Instalación de la librería jsoncpp

	- Bajar el ultimo release de este link

		a. https://github.com/open-source-parsers/jsoncpp/archive/master.zip

	- Descomprimir el archivo "jsoncpp-master"

	- Ingresar a la carpeta "jsoncpp-master" en una terminal

	- Entrar con sudo su en la terminal

	- Ejecutar los siguientes comandos

		mkdir -p build/debug

		cd build/debug

		cmake -DCMAKE_BUILD_TYPE=debug -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G 			"Unix Makefiles" ../..

    	make

	- Ingresar a la carpeta "/src/lib_json"

	- Ejecutar el comando: cp -a libjsoncpp.a /usr/local/lib

4 - Bajar dependecia de CURL y  curlpp
	- sudo apt-get install libcurl4-openssl-dev

 

