cmake_minimum_required(VERSION 3.5)

set(TESTS_CONTAINER tests_container)

add_executable(${TESTS_CONTAINER})

set_target_properties(${TESTS_CONTAINER}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CONTAINER_DIR ../../src/container)

set(SRC
  startup_test.cpp
  test_container.cpp
  ${CONTAINER_DIR}/clist.hpp
  ${CONTAINER_DIR}/clist.cpp
)

target_include_directories(${TESTS_CONTAINER}
  PUBLIC
    ${CONTAINER_DIR}
  PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_sources(${TESTS_CONTAINER} PRIVATE ${SRC})

target_link_libraries(${TESTS_CONTAINER} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME ${TESTS_CONTAINER} COMMAND ${TESTS_CONTAINER})
