#include <boost/test/unit_test.hpp>

#include <string>

#include "quick_sort.hpp"

BOOST_AUTO_TEST_CASE(quick_sort_queue_empty)
{
  std::queue<char> q;
  const std::queue<char> target; 

  Sort::quick_sort(q);

  BOOST_CHECK(q == target);
}

BOOST_AUTO_TEST_CASE(quick_sort_queue_int)
{
  std::queue<int> q{ {6, 5, 4, 3, 2, 1, 1, 123, 54656} };
  const std::queue<int> target{ {1, 1, 2, 3, 4, 5, 6, 123, 54656} }; 

  Sort::quick_sort(q);

  BOOST_CHECK(q == target);
}


BOOST_AUTO_TEST_CASE(quick_sort_queue_std_string)
{
  std::queue<std::string> q{ {"123", "456", "789", "101112", "131415"} };
  const std::queue<std::string> target{ {"101112", "123", "131415", "456", "789"} }; 

  Sort::quick_sort(q);

  BOOST_CHECK(q == target);
}
