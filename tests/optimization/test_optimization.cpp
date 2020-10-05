#include <boost/test/unit_test.hpp>

#include <vector>
#include <utility> // std::forward
#include <iostream>

#include "simplex_method.hpp"

namespace
{

template <class T>
using Matrix = std::vector<std::vector<T>>;

class SimplexPublicMembers : public Optimization::Simplex
{
public:
  using Optimization::Simplex::matrix_;

  template <class... Ts>
  explicit SimplexPublicMembers(Ts&&... ts)
    : Optimization::Simplex(std::forward<Ts>(ts)...)
  { }
};

} // anonymous namespace

BOOST_AUTO_TEST_CASE(simplex_method_constructor)
{
  const std::vector<int> target = { 5, 4, 5 };

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
  const std::vector<int> target = { 9, 10, 16 };

  const Matrix<int> matrix = {
    {360, 18, 15, 12},
    {192,  6,  4,  8},
    {180,  5,  3,  3}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 400);
}

BOOST_AUTO_TEST_CASE(simplex_method_task_2_3)
{
  const std::vector<int> target = { 3, 3, 5 };

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
  const std::vector<int> target = { 4, 3, 5 };

  const Matrix<int> matrix = {
    {383,  1,  2, 18},
    {288,  1, 18,  3},
    {362,  5, 11, 15}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 144);
}

BOOST_AUTO_TEST_CASE(simplex_method_task_3_3)
{
  const std::vector<int> target = { 4, 4, 5 };

  const Matrix<int> matrix = {
    {355,  7, 4, 17},
    {400,  3, 5,  4},
    {302,  4, 4,  8}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 288);
}

BOOST_AUTO_TEST_CASE(simplex_method_task_3_4)
{
  const std::vector<int> target = { 5, 4, 3 };

  const Matrix<int> matrix = {
    {267, 19, 10, 9},
    {369,  7,  6, 1},
    {292, 16, 11, 5}
  };

  Optimization::Simplex simplex{target, matrix};

  const auto result = simplex.calculate();

  BOOST_CHECK(result == 128);
}
