cmake_minimum_required(VERSION 3.5)

set(TESTS_SORT tests_sort)

add_executable(${TESTS_SORT})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(SORT_DIR ../../src/sort)

set(SRC
  startup_test.cpp
  test_sort.cpp
)

target_include_directories(${TESTS_SORT}
  PUBLIC
    ${SORT_DIR}
  PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_sources(${TESTS_SORT} PRIVATE ${SRC})

target_link_libraries(${TESTS_SORT} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME ${TESTS_SORT} COMMAND ${TESTS_SORT})
