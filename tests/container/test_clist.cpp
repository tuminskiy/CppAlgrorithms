#include <boost/test/unit_test.hpp>

#include "clist.hpp"

using namespace Container;

BOOST_AUTO_TEST_CASE(container_clist_size) // 1
{
  CList<int> clist;

  BOOST_CHECK(clist.size() == 0);
}

BOOST_AUTO_TEST_CASE(container_clist_push) // 2
{
  CList<int> clist;

  clist.push_back(2);
  clist.push_front(1);

  BOOST_CHECK(clist.size() == 2);
}

BOOST_AUTO_TEST_CASE(container_clist_pop) // 3
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(2);

  clist.pop_front();
  BOOST_CHECK(clist.size() == 1);

  clist.pop_back();
  BOOST_CHECK(clist.size() == 0);
}

BOOST_AUTO_TEST_CASE(container_clist_operator_square_brackets) // 4
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(2);
  clist.push_back(3);

  BOOST_CHECK(clist[0] == 1);
  BOOST_CHECK(clist[1] == 2);
  BOOST_CHECK(clist[2] == 3);
}

BOOST_AUTO_TEST_CASE(container_clist_front_back) // 5
{
  CList<int> clist;

  clist.push_back(2);
  clist.push_front(1);

  BOOST_CHECK(clist.front() == 1);
  BOOST_CHECK(clist.back() == 2);

  clist.front() = 2;
  clist.back() = 1;

  BOOST_CHECK(clist.front() == 2);
  BOOST_CHECK(clist.back() == 1);
}

BOOST_AUTO_TEST_CASE(container_clist_begin_end) // 6
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(2);
  clist.push_back(3);

  auto first = clist.begin();
  auto last = clist.end();

  BOOST_CHECK(*first == 1);
  BOOST_CHECK(*(last - 1) == 3);

  ++first;
  --last;
 
  BOOST_CHECK(first != last);
  BOOST_CHECK(!(first + 1 != last));
}

BOOST_AUTO_TEST_CASE(container_clist_insert_erase) // 7
{
  CList<int> clist;

  clist.push_back(1);
  clist.push_back(3);

  auto it = clist.insert(clist.begin(), 2);
  BOOST_CHECK(*it == 2);

  clist.erase(it);
  BOOST_CHECK(clist[1] == 3);
}
