#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "clist.hpp"

using namespace Container;

BOOST_AUTO_TEST_CASE(container_size)
{
  CList<int> clist;
  BOOST_CHECK(clist.size() == 0);
}

BOOST_AUTO_TEST_CASE(container_push)
{
  CList<int> clist;

  clist.push_back(2);
  clist.push_front(1);
  clist.push_back(3);

  BOOST_CHECK(clist.size() == 3);
}

BOOST_AUTO_TEST_CASE(container_front_back)
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(2);
  clist.push_back(3);

  BOOST_CHECK(clist.front() == 1);
  BOOST_CHECK(clist.back() == 3);

  clist.front() = 0;
  clist.back() = 4;

  BOOST_CHECK(clist.front() == 0);
  BOOST_CHECK(clist.back() == 4);
}

BOOST_AUTO_TEST_CASE(container_pop)
{
  CList<int> clist;

  clist.pop_front();
  BOOST_CHECK(clist.size() == 0);

  clist.pop_back();
  BOOST_CHECK(clist.size() == 0);

  clist.push_back(1);
  clist.push_back(2);
  clist.pop_back();
  BOOST_CHECK(clist.size() == 1);

  clist.pop_back();
  BOOST_CHECK(clist.size() == 0);

  clist.push_front(2);
  clist.push_front(1);
  clist.pop_front();
  BOOST_CHECK(clist.size() == 1);
  
  clist.pop_front();
  BOOST_CHECK(clist.size() == 0);
}

BOOST_AUTO_TEST_CASE(container_operator_square_brackets)
{
  CList<int> clist;

  clist.push_back(2);
  clist.push_front(1);
  clist.push_back(3);

  BOOST_CHECK(clist[0] == 1);
  BOOST_CHECK(clist[1] == 2);
  BOOST_CHECK(clist[2] == 3);
}

BOOST_AUTO_TEST_CASE(container_remove)
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(2);
  clist.push_back(3);

  clist.remove(1);

  BOOST_CHECK(clist.size() == 2);
  BOOST_CHECK(clist[0] == 1);
  BOOST_CHECK(clist[1] == 3);
}

BOOST_AUTO_TEST_CASE(container_iterator)
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(2);

  auto first = clist.begin();
  BOOST_CHECK(*first == 1);

  auto last = clist.end();
  BOOST_CHECK(*last == 2);

  first++;
  BOOST_CHECK(first == last);
}
