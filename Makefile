Objects = src/AppServer.cpp src/mongoose.c src/Private/Log.cpp src/Private/Server/Connection.cpp src/Private/Server/ApplicationServerConnection.cpp src/Private/Server/HttpRequest.cpp src/Private/Server/HttpRequestHandler.cpp src/Private/Server/RestServer.cpp src/Private/Server/SharedServerConnection.cpp

CompiledObjects = AppServer.o mongoose.o Log.o Connection.o ApplicationServerConnection.o HttpRequest.o HttpRequestHandler.o RestServer.o SharedServerConnection.o

all: Server Test
Test:
	$(CXX) -std=c++11 -c googleTest.cpp -I"./include"
	$(CXX) -o gTest googleTest.o -L./lib -lgtest -lz -lpthread -lrt
Server:
	$(CXX) -std=c++11 -c $(Objects) -I"./src" -I"./src/Public" -I"./include"
	$(CXX) -o ApplicationServer $(CompiledObjects)

