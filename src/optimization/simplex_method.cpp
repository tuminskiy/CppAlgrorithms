#include "simplex_method.hpp"

#include <algorithm>
#include <numeric> // accumulate

namespace Optimization
{

using namespace std;

Simplex::Simplex(const vector<int>& target, const Matrix<int>& matrix)
  : iter_count_{0}
{
  /*
   *  Initial matrix format:
   *  {
   *    {0, b1, a11, a12, a13, ... , a1n, 1, 0, 0, ... , 0n},
   *    {0, b2, a21, a22, a23, ... , a2n, 0, 1, 0, ... , 0n},
   *    {0, b3, a31, a32, a33, ... , a3n, 0, 0, 1, ... , 0n},
   *    ...
   *    {0, bn, an1, an2, an3, ... , anm, 0, 0, 0, ... , 1},
   *    {0,  0, -c1, -c2, -c3, ... , -cn, 0, 0, 0, ... , 0}
   *  }
   *
   */

  target_.reserve(target.size());
  transform(begin(target), end(target), back_inserter(target_),
    [](auto v) { return static_cast<double>(v); }
  );

  const auto c_row = matrix.size();
  const auto c_col = matrix.at(0).size();

  matrix_.resize(c_row + 1, vector<double>(1u + c_col + c_row, 0.0));
  
  size_t index = 0;

  for_each(begin(matrix_), prev(end(matrix_)),
    [&](auto& row) {
      const auto& base_row = matrix[index];

      auto it = next(begin(row));

      for (double base_col : base_row) {
        *it++ = static_cast<int>(base_col);
      }

      *(it + index) = 1;

      ++index;
    }
  );

  auto it = begin(matrix_.back()) + 2;
  for (double value : target_) {
    *it++ = -static_cast<int>(value);
  }
}

int Simplex::calculate()
{
  while (!is_optimal())
    simplex();

  if (iter_count_ > 1000)
    return -1;

  return static_cast<int>(matrix_.back()[1]);
}

void Simplex::simplex()
{
  const auto col_index = index_of_pivot_column();
  const auto row_index = index_of_pivot_row(col_index);

  pivot(row_index, col_index);

  ++iter_count_;
}

bool Simplex::is_optimal() const
{
  if (iter_count_ > 1000)
    return true;

  const auto& last_row = matrix_.back();

  return all_of(begin(last_row), end(last_row),
    [](double v) { return v >= 0.0; }
  );
}

size_t Simplex::index_of_pivot_column() const
{
  const auto& last_row = matrix_.back();

  const auto it = min_element(begin(last_row), end(last_row));

  return it - begin(last_row);
}

size_t Simplex::index_of_pivot_row(size_t col_index) const
{
  vector<double> v;
  v.reserve(target_.size());

  transform(begin(matrix_), prev(end(matrix_)), back_inserter(v),
    [&](const auto& row) {
      return row[1] / row[col_index];
    }
  );

  const auto it = min_element(begin(v), end(v));

  return it - begin(v);
}

void Simplex::pivot(size_t row_i, size_t col_i)
{
  const auto value = matrix_[row_i][col_i];
  const auto prev_matrix = matrix_;
  
  auto& p_row = matrix_[row_i];

  p_row.front() = target_[col_i - target_.size() + 1];

  transform(next(begin(p_row)), end(p_row), next(begin(p_row)),
    [&value](double v) { return v / value; }
  );
  
  for (size_t i = 0; i < matrix_.size(); i++) {
    if (i == row_i)
      continue;
  
    matrix_[i][col_i] = 0.0;
    
    for (size_t j = 1; j < matrix_[i].size(); j++) {
      // if last row and second col or 'j' is index of pivot col
      if (i + 1 == matrix_.size() && j == 1 || j == col_i) 
        continue;

      const auto value_1 = prev_matrix[i][j];
      const auto value_2 = prev_matrix[i][col_i];
      const auto value_3 = matrix_[row_i][j];

      matrix_[i][j] = value_1 - value_3 * value_2;
    }
  }

  const auto sum = accumulate(begin(matrix_), prev(end(matrix_)), 0.0,
    [](double init, const auto& row) {
      return init + row[0] * row[1];
    }
  );

  matrix_.back()[1] = sum;
}

} // namespace Optimization
