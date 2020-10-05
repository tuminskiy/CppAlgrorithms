cmake_minimum_required(VERSION 3.5)

set(TESTS_UTILITY tests_utility)

add_executable(${TESTS_UTILITY})

set_target_properties(${TESTS_UTILITY}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(UTIL_DIR ../../src/util)

set(SRC
  startup_test.cpp
  test_util.cpp
  ${UTIL_DIR}/range_offset.cpp
)

target_include_directories(${TESTS_UTILITY}
  PUBLIC
    ${UTIL_DIR}
  PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_sources(${TESTS_UTILITY} PRIVATE ${SRC})

target_link_libraries(${TESTS_UTILITY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME ${TESTS_UTILITY} COMMAND ${TESTS_UTILITY})
