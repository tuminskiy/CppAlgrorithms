#include <boost/test/unit_test.hpp>

#include "graph.hpp"

BOOST_AUTO_TEST_CASE( graph_case_1 )
{
  Container::Graph graph;

  graph.add_node("0");
  graph.add_node("1");
  graph.add_node("2");
  graph.add_node("3");
  graph.add_node("4");

  graph.add_adj("0", "1", 13);
  graph.add_adj("0", "3", 7);

  graph.add_adj("1", "2", 2);

  graph.add_adj("2", "0", 3);
  graph.add_adj("2", "4", 3);

  graph.add_adj("3", "0", 8);
  graph.add_adj("3", "1", 2);
  graph.add_adj("3", "4", 9);

  graph.add_adj("4", "0", 7);

  BOOST_CHECK( graph.radius() == 7 );
}


BOOST_AUTO_TEST_CASE( graph_case_2 )
{
  Container::Graph graph;

  graph.add_node("0");
  graph.add_node("1");
  graph.add_node("2");
  graph.add_node("3");
  graph.add_node("4");
  graph.add_node("5");

  graph.add_adj("0", "1", 7);
  graph.add_adj("0", "2", 9);
  graph.add_adj("0", "5", 14);

  graph.add_adj("1", "0", 7);
  graph.add_adj("1", "2", 10);
  graph.add_adj("1", "3", 15);

  graph.add_adj("2", "0", 9);
  graph.add_adj("2", "1", 10);
  graph.add_adj("2", "3", 11);
  graph.add_adj("2", "5", 2);

  graph.add_adj("3", "1", 15);
  graph.add_adj("3", "2", 11);
  graph.add_adj("3", "4", 6);

  graph.add_adj("4", "3", 6);
  graph.add_adj("4", "5", 9);

  graph.add_adj("5", "0", 14);
  graph.add_adj("5", "2", 2);
  graph.add_adj("5", "4", 9);

  BOOST_CHECK( graph.radius() == 11 );
}
