#include <boost/test/unit_test.hpp>

#include <sstream>

#include "flat_rbst.hpp"

using namespace Container;

BOOST_AUTO_TEST_CASE(container_flat_rbst_construct) // 1
{
  FlatRbst<int> fb;
  
  unsigned int count = 0;

  const auto counter = [&count](const auto& value) {
    ++count;
  };

  fb.nlr_iterate(counter);

  BOOST_CHECK(count == 0);
}

BOOST_AUTO_TEST_CASE(container_flat_rbst_insert) // 2
{
  FlatRbst<int> fb;

  unsigned int count = 0;
  std::stringstream ss;

  const auto lambda = [&count, &ss](const auto& value) {
    ++count;
    ss << value;
  };

  fb.insert(5);
  fb.nlr_iterate(lambda);

  BOOST_CHECK(count == 1);
  BOOST_CHECK(ss.str() == "5");
}
