cmake_minimum_required(VERSION 3.5)
project(STACK CXX)

set(LIB_SOURCES "stack.cpp")
set(TEST_SOURCES "main.cpp")

add_library(stack STATIC ${LIB_SOURCES})

add_executable(test_stack ${TEST_SOURCES})
target_link_libraries(test_stack stack)
