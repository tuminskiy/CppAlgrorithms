#pragma once

#include <utility>

namespace Utility
{

struct Offset
{
  std::size_t offset = 0;
};

Offset offset(std::size_t value);

template <class Iterator>
class View
{
  Iterator begin_;
  Iterator end_;

public:
  explicit View(Iterator begin, Iterator end)
    : begin_{begin}, end_{end}
  { }

  constexpr auto begin() const { return begin_; }
  constexpr auto end() const { return end_; }
};

template <class Range>
auto operator| (Range&& range, Offset o)
{
  return View {
    std::begin(std::forward<Range>(range)) + o.offset,
    std::end(std::forward<Range>(range)),
  };
}

} // Utility
