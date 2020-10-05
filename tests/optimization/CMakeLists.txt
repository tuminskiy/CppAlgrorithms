cmake_minimum_required(VERSION 3.5)

set(TESTS_OPTIMIZATION tests_optimization)

add_executable(${TESTS_OPTIMIZATION})

set_target_properties(${TESTS_OPTIMIZATION}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(OPTIMIZATION_DIR ../../src/optimization)

set(SRC
  startup_test.cpp
  test_optimization.cpp
  ${OPTIMIZATION_DIR}/simplex_method.cpp
)

target_include_directories(${TESTS_OPTIMIZATION}
  PRIVATE
    ${OPTIMIZATION_DIR}
    ${Boost_INCLUDE_DIR}
)

target_sources(${TESTS_OPTIMIZATION} PRIVATE ${SRC})

target_link_libraries(${TESTS_OPTIMIZATION} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME ${TESTS_OPTIMIZATION} COMMAND ${TESTS_OPTIMIZATION})
