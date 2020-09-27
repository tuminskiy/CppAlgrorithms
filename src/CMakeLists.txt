cmake_minimum_required(VERSION 3.5)

set(BIN_NAME program)

add_executable(${BIN_NAME})

set(SRC main.cpp)

target_sources(${BIN_NAME} PRIVATE ${SRC})
