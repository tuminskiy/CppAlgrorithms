#include <boost/test/unit_test.hpp>

#include <vector>
#include <sstream>
#include <string>

#include "range_offset.hpp"

BOOST_AUTO_TEST_CASE(range_offset_1)
{
  std::ostringstream oss;
  std::vector<int> v = {1, 2, 3, 4, 5};

  for (auto i : v | Utility::offset(1)) {
    oss << i << " ";
  }

  const std::string target = "2 3 4 5 ";

  BOOST_CHECK(target == oss.str());
}
