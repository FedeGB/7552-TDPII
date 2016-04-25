cmake_minimum_required (VERSION 2.6)
project (Tinder)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

option(CHECK_COVERAGE "Activa flags para checkear test coverage" ON)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -LDFLAGS= -pthread -DMONGOOSE_ENABLE_THREADS --coverage")

link_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories ("${PROJECT_SOURCE_DIR}/include")

enable_testing()
find_package(GTest REQUIRED)

set(TEST_LINK_LIBS libjsoncpp.a z pthread rt)

file( GLOB FILES src/Conversation.cpp src/Database.cpp src/Manager.cpp src/Message.cpp src/Server.cpp src/User.cpp src/mongoose.c src/Factories/* src/HttpEvents/*)

file( GLOB TESTS src/Tests/*)

set(SOURCE_FILES ${FILES} ${TESTS})

add_executable (tests test/googleTest.cpp ${TESTS} ${SOURCE_FILES} )
add_executable (main src/main.cpp ${SOURCE_FILES})

find_package(RocksDB)
if(ROCKSDB_FOUND)
	include_directories("${ROCKSDB_INCLUDE_DIRS}")
	target_link_libraries(main ${ROCKSDB_LIBRARIES})
	target_link_libraries(tests ${ROCKSDB_LIBRARIES})
	target_link_libraries(main "-lgcov -lsnappy -lgflags -lz -lbz2")
	target_link_libraries(tests "-lgcov -lsnappy -lgflags -lz -lbz2")
else()
	message(FATAL_ERROR "No se encuentra RocksDB")
endif()

if(CHECK_COVERAGE)
	set_target_properties(tests PROPERTIES COMPILE_FLAGS "--coverage -lgcov -fprofile-arcs -ftest-coverage -g -ggdb -O0")
	target_link_libraries(tests "-fprofile-arcs -ftest-coverage")
	set_target_properties(main PROPERTIES COMPILE_FLAGS "--coverage -lgcov -fprofile-arcs -ftest-coverage -g -ggdb -O0")
	target_link_libraries(main "-fprofile-arcs -ftest-coverage")
endif()

target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} ${TEST_LINK_LIBS})
target_link_libraries(main ${GTEST_BOTH_LIBRARIES} ${TEST_LINK_LIBS})




