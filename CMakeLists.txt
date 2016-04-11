cmake_minimum_required (VERSION 2.6)
project (Tinder)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -LDFLAGS= -pthread -lpthread -DMONGOOSE_ENABLE_THREADS")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsnappy -lgflags -lz -lbz2")



link_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories ("${PROJECT_SOURCE_DIR}/include")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_LINK_LIBS libgtest.a libjsoncpp.a z pthread rt)

file( GLOB FILES src/Conversation.cpp src/Database.cpp src/Manager.cpp src/Message.cpp src/Server.cpp src/User.cpp src/mongoose.c)

file( GLOB TESTS src/Tests/*)

set(SOURCE_FILES ${FILES} ${TESTS})

add_executable (tests test/googleTest.cpp ${TESTS} ${SOURCE_FILES} )
add_executable (main src/main.cpp ${SOURCE_FILES})

find_package(RocksDB)
if(ROCKSDB_FOUND)
	include_directories("${ROCKSDB_INCLUDE_DIRS}")
	target_link_libraries(main ${ROCKSDB_LIBRARIES})
	target_link_libraries(tests ${ROCKSDB_LIBRARIES})
	#target_link_libraries(dbtest ${ROCKSDB_LIBRARIES})
	#set(LIBS ${LIBS} ${ROCKSDB_LIBRARIES})
else()
	message(FATAL_ERROR "No se encuentra RocksDB")
endif()

target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} ${TEST_LINK_LIBS})
target_link_libraries(main ${GTEST_BOTH_LIBRARIES} ${TEST_LINK_LIBS})
TARGET_LINK_LIBRARIES(main ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(main ${ZLIB_LIBRARIES})
TARGET_LINK_LIBRARIES(main ${BZIP2_LIBRARIES})




