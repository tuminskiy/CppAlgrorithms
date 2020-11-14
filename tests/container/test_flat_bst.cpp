#include <boost/test/unit_test.hpp>

#include <sstream>

#include "flat_bst.hpp"

using namespace Container;

BOOST_AUTO_TEST_CASE(container_flat_bst_construct) // 1
{
  FlatBst<int> fb;
  
  unsigned int count = 0;

  const auto counter = [&count](const auto& value) {
    ++count;
  };

  fb.nlr_iterate(counter);

  BOOST_CHECK(count == 0);
}

BOOST_AUTO_TEST_CASE(container_flat_bst_insert) // 2
{
  FlatBst<int> fb;

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
  
  count = 0;
  ss.str(std::string{});

  fb.insert({2, 7, 1, 3, 6, 8});
  fb.nlr_iterate(lambda);

  BOOST_CHECK(count == 7);
  BOOST_CHECK(ss.str() == "5213768");
}

BOOST_AUTO_TEST_CASE(container_flat_bst_iterate)
{
  FlatBst<int> fb;

  unsigned int count = 0;
  std::stringstream ss;

  const auto lambda = [&count, &ss](const auto& value) {
    ++count;
    ss << value;
  };

  fb.insert({5, 3, 7, 2, 4, 6, 8});

  fb.nlr_iterate(lambda);

  BOOST_CHECK(count == 7);
  BOOST_CHECK(ss.str() == "5324768");

  count = 0;
  ss.str(std::string{});

  fb.lnr_iterate(lambda);

  BOOST_CHECK(count == 7);
  BOOST_CHECK(ss.str() == "2345678");

  count = 0;
  ss.str(std::string{});

  fb.lrn_iterate(lambda);

  BOOST_CHECK(count == 7);
  BOOST_CHECK(ss.str() == "2436875");

}
