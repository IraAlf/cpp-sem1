cmake_minimum_required(VERSION 3.8)
project(HW2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")

add_subdirectory(dynamic)
add_subdirectory(static)



enable_testing()



find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(tests.out project/dynamic/tests/test.cpp)
set_target_properties(tests.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
target_link_libraries(tests.out ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

target_link_libraries(tests PRIVATE dn_lib ${CMAKE_DL_LIBS}))
target_link_libraries(tests PUBLIC st_lib )



