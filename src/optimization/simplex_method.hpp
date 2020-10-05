#pragma once

#include <vector>

namespace Optimization
{

template <class T>
using Matrix = std::vector<std::vector<T>>;

class Simplex
{
public:
  
  /*
   *  Target function:
   *    c1*x1 + c2*x2 + ... + cn*cx -> max
   *
   *  Restrictions:
   *    a11*x11 + a12*x12 + ... + a1n*x1n <= b1 
   *    a21*a21 + a22*x22 + ... + a2n*x2n <= b2
   *    ...
   *    an1*ax1 + an2*xn2 + ... + anm*xnm <= bn
   *
   *  Format example
   *
   *    Matrix should be:
   *    {
   *      {b1, a11, a12, ... , a1n},
   *      {b2, a21, a22, ... , a2n},
   *      ...
   *      {bn, an1, an2, ... , anm}
   *    }
   *
   *    Target should be:
   *    { c1, c2, ... , cn }
   *
   */

  explicit Simplex(const std::vector<int>& target, const Matrix<int>& matrix);
  virtual ~Simplex() = default;

  int calculate();

private:
  void simplex();
  
  bool is_optimal() const;
  
  size_t index_of_pivot_column() const;
  size_t index_of_pivot_row(size_t col_index) const;

  void pivot(size_t row_index, size_t col_index);

protected:
  std::vector<double> target_;
  Matrix<double> matrix_;
  size_t iter_count_;
};

} // namespace Optimization
