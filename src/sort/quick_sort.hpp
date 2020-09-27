#include <queue>

namespace Sort
{

template <class T>
void quick_sort(std::queue<T>& q)
{
  if (q.empty())
    return;

  std::queue<T> lhs; // values less than pivot
  std::queue<T> equal; // values equal pivot
  std::queue<T> rhs; // values greater than pivot

  const auto pivot = q.back();
  
  while (!q.empty()) {
    const auto value = q.front();

    if (value < pivot)
      lhs.push(value);
    else if (pivot < value)
      rhs.push(value);
    else // value == pivot
      equal.push(value);

    q.pop();
  }

  quick_sort(lhs);
  quick_sort(rhs);

  const auto move_queue = [](std::queue<T>& from, std::queue<T>& to) {
    while (!from.empty()) {
      to.push(from.front());
      from.pop();
    }
  };

  move_queue(lhs, q);
  move_queue(equal, q);
  move_queue(rhs, q);
}

} // namespace Sort
