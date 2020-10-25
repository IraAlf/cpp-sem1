cmake_minimum_required(VERSION 3.8)
project(HW1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")


include_directories(project/headers)

include_directories(project/tests)

enable_testing()

add_library(findmaxlib STATIC ${PROJECT_SOURCE_DIR}/project/src/find_max.c)
add_library(findmaxparalellib SHARED ${PROJECT_SOURCE_DIR}/project/src/find_max_paral.c)




find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(tests project/tests/test.cpp)
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} findmaxlib findmaxparalellib)



