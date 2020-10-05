#include <boost/test/unit_test.hpp>

#include <vector>
#include <utility> // forward
#include <iostream>

#include "simplex_method.hpp"

using namespace std;

namespace
{

template <class T>
using Matrix = vector<vector<T>>;

class SimplexPublicMembers : public Optimization::Simplex
{
public:
  using Optimization::Simplex::matrix_;

  template <class... Ts>
  explicit SimplexPublicMembers(Ts&&... ts)
    : Optimization::Simplex(forward<Ts>(ts)...)
  { }
};

} // anonymous namespace


BOOST_AUTO_TEST_CASE(simplex_method_constructor)
{
  const vector<int> target = { 5, 4, 5 };

  const Matrix<int> matrix = {
    {390, 17, 3,  5},
    {251, 13, 7, 12},
    {266,  7, 7,  3}
  };
 
  SimplexPublicMembers simplex{target, matrix};

  const Matrix<double> result = {
    {0, 390, 17,  3,  5, 1, 0, 0},
    {0, 251, 13,  7, 12, 0, 1, 0},
    {0, 266,  7,  7,  3, 0, 0, 1},
    {0,   0, -5, -4, -5, 0, 0, 0}
  };

  BOOST_CHECK(simplex.matrix_ == result);
}


BOOST_AUTO_TEST_CASE(simplex_method_task_from_example)
{
  const vector<int> target = { 9, 10, 16 };

  const Matrix<int> matrix = {
    {360, 18, 15, 12},
    {192,  6,  4,  8},
    {180,  5,  3,  3}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 400);
}


BOOST_AUTO_TEST_CASE(simplex_method_task_1_3)
{
  const vector<int> target = { 5, 4, 5 };

  const Matrix<int> matrix = {
    {390, 17, 3,  5},
    {251, 13, 7, 12},
    {266,  7, 7,  3}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 128);
  cerr << "tasl 1.3: " << result << "\n\n";
}

BOOST_AUTO_TEST_CASE(simplex_method_task_1_4)
{
  const vector<int> target = { 6, 1, 5 };

  const Matrix<int> matrix = {
    {242,  7, 17, 17},
    {329, 16,  5,  1},
    {325, 18,  3,  3}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 128);
  cerr << "tasl 1.4: " << result << "\n\n";
}


BOOST_AUTO_TEST_CASE(simplex_method_task_2_3)
{
  const vector<int> target = { 3, 3, 5 };

  const Matrix<int> matrix = {
    {271,  4, 5, 13},
    {288, 17, 7, 11},
    {355,  1, 4, 10}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 157);
}

BOOST_AUTO_TEST_CASE(simplex_method_task_2_4)
{
  const vector<int> target = { 4, 3, 5 };

  const Matrix<int> matrix = {
    {383,  1,  2, 18},
    {288,  1, 18,  3},
    {362,  5, 11, 15}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 144);
  cerr << "task 2.4: " << result << "\n\n";
}


BOOST_AUTO_TEST_CASE(simplex_method_task_3_3)
{
  const vector<int> target = { 4, 4, 5 };

  const Matrix<int> matrix = {
    {355,  7, 4, 17},
    {400,  3, 5,  4},
    {302,  4, 4,  8}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 288);
  cerr << "task 3.3: " << result << "\n\n";
}

BOOST_AUTO_TEST_CASE(simplex_method_task_3_4)
{
  const vector<int> target = { 5, 4, 3 };

  const Matrix<int> matrix = {
    {267, 19, 10, 9},
    {369,  7,  6, 1},
    {292, 16, 11, 5}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 128);
  cerr << "task 3.4: " << result << "\n\n";
}


BOOST_AUTO_TEST_CASE(simplex_method_task_4_3)
{
  const vector<int> target = { 2, 4, 3 };

  const Matrix<int> matrix = {
    {263, 4, 18,  8},
    {326, 6, 17,  3},
    {293, 7, 14, 12}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 83);
}

BOOST_AUTO_TEST_CASE(simplex_method_task_4_4)
{
  const vector<int> target = { 3, 3, 7 };

  const Matrix<int> matrix = {
    {346,  3,  3, 18},
    {346, 17, 14, 18},
    {255, 16, 10,  1}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 134);
}


BOOST_AUTO_TEST_CASE(simplex_method_task_5_3)
{
  const vector<int> target = { 4, 4, 4 };

  const Matrix<int> matrix = {
    {325, 18,  8,  7},
    {364,  3, 11, 14},
    {254,  8,  4,  2}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 153);
  cerr << "task 5.3: " << result << "\n\n";
}

BOOST_AUTO_TEST_CASE(simplex_method_task_5_4)
{
  const vector<int> target = { 4, 5, 5 };

  const Matrix<int> matrix = {
    {241,  7, 14, 11},
    {282, 18, 13, 18},
    {329,  3, 14, 11}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 95);
}


BOOST_AUTO_TEST_CASE(simplex_method_task_6_3)
{
  const vector<int> target = { 4, 5, 2 };

  const Matrix<int> matrix = {
    {308,  9, 13,  3},
    {400, 12,  4, 13},
    {293,  3, 17,  1}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 128);
  cerr << "task 6.3: " << result << "\n\n";
}

BOOST_AUTO_TEST_CASE(simplex_method_task_6_4)
{
  const vector<int> target = { 6, 5, 3 };

  const Matrix<int> matrix = {
    {325, 18, 18, 18},
    {244,  7,  7,  2},
    {271, 19, 14,  7}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 95);
  cerr << "task 6.4: " << result << "\n\n";
}


BOOST_AUTO_TEST_CASE(simplex_method_task_7_3)
{
  const vector<int> target = { 2, 2, 2 };

  const Matrix<int> matrix = {
    {358,  6, 4,  9},
    {260, 18, 4,  2},
    {260, 13, 4, 10}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 130);
}

BOOST_AUTO_TEST_CASE(simplex_method_task_7_4)
{
  const vector<int> target = { 4, 5, 4 };

  const Matrix<int> matrix = {
    {302,  3, 17,  7},
    {331,  1,  7,  5},
    {246, 14, 11, 11}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 116);
  cerr << "task 7.4: " << result << "\n\n";
}


BOOST_AUTO_TEST_CASE(simplex_method_task_8_3)
{
  const vector<int> target = { 7, 2, 4 };

  const Matrix<int> matrix = {
    {376, 17, 11, 14},
    {303, 17,  2,  6},
    {334, 18,  3,  9}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 128);
  cerr << "task 8.3: " << result << "\n\n";
}

BOOST_AUTO_TEST_CASE(simplex_method_task_8_4)
{
  const vector<int> target = { 5, 4, 5 };

  const Matrix<int> matrix = {
    {357, 14, 14, 15},
    {275, 10,  2,  7},
    {270, 18,  6, 10}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 125);
  cerr << "task 8.4: " << result << "\n\n";
}
