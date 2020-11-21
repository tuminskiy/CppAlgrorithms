#pragma once

#include <vector>
#include <optional>

namespace Container::Detail {

template <class T>
struct FlatRbstNode
{
  FlatRbstNode(const T& value);

  template <class U>
  friend bool operator< (const U& lhs, const FlatRbstNode<U>& rhs);

  template <class U>
  friend bool operator< (const FlatRbstNode<U>& lhs, const U& rhs);

  T value;
  size_t size;
};

}

namespace Container {

template <class T>
class FlatRbst
{
public:
  virtual ~FlatRbst() = default;

  void insert(const T& value);
  void insert(const std::initializer_list<T>& il);

  template <class Func> void nlr_iterate(Func f);
  template <class Func> void lnr_iterate(Func f);
  template <class Func> void lrn_iterate(Func f);

private:
  using Container = std::vector<std::optional<Detail::FlatRbstNode<T>>>;
  using PairOfVectors = std::pair<std::vector<T>, std::vector<T>>;

  Container data_;

  size_t left(size_t parent) const;
  size_t right(size_t parent) const;
  size_t parent(size_t index) const;

  bool is_valid(size_t index) const;

  size_t get_size(size_t index) const;
  void fix_size(size_t index);

  void insert(size_t index, const T& value);
  void insert_as_root(const T& value, size_t index);

  PairOfVectors split(const T& value, size_t index);

  template <class Func> void nlr_iterate(size_t index, Func f);
  template <class Func> void lnr_iterate(size_t index, Func f);
  template <class Func> void lrn_iterate(size_t index, Func f);
};

} // namespace Container

/*
  IMPLEMENTATION
*/
namespace Container::Detail {

template <class T>
FlatRbstNode<T>::FlatRbstNode(const T& _value)
  : value(_value)
  , size(1)
{ }


template <class T>
bool operator< (const T& lhs, const FlatRbstNode<T>& rhs)
{
  return lhs < rhs.value;
}

template <class T>
bool operator< (const FlatRbstNode<T>& lhs, const T& rhs)
{
  return lhs.value < rhs;
}

} // Container::Detail

namespace Container { 

template <class T>
void FlatRbst<T>::insert(const T& value) { insert(0, value); }

template <class T>
void FlatRbst<T>::insert(const std::initializer_list<T>& il)
{
  for (const auto& value : il)
    insert(value);
}


template <class T> template <class Func>
void FlatRbst<T>::nlr_iterate(Func f) { return nlr_iterate(0, f); }

template <class T> template <class Func>
void FlatRbst<T>::lnr_iterate(Func f) { return lnr_iterate(0, f); }

template <class T> template <class Func>
void FlatRbst<T>::lrn_iterate(Func f) { return lrn_iterate(0, f); }


template <class T>
size_t FlatRbst<T>::left(size_t parent) const { return parent * 2 + 1; }

template <class T>
size_t FlatRbst<T>::right(size_t parent) const { return parent * 2 + 2; }

template <class T>
size_t FlatRbst<T>::parent(size_t index) const { return (index - 1) / 2; }


template <class T>
bool FlatRbst<T>::is_valid(size_t index) const
{
  return index < data_.size() && data_[index];
}


template <class T>
size_t FlatRbst<T>::get_size(size_t index) const
{
  return data_[index] ? data_[index]->size : 0;
}

template <class T>
void FlatRbst<T>::fix_size(size_t index)
{
  data_[index]->size = get_size(left(index)) + get_size(right(index)) + 1;
}


template <class T>
void FlatRbst<T>::insert(size_t index, const T& value)
{
  if (data_.size() <= index)
    data_.resize(index + 1);

  const auto rand = std::rand() % (get_size(index) + 1);

  if (rand == 0)
    insert_as_root(value, index);
  else if (value < data_[index])
    insert(value, left(index));
  else if (data_[index] < value)
    insert(value, right(index));
}

template <class T>
void FlatRbst<T>::insert_as_root(const T& value, size_t index)
{
  const auto [smaller, bigger] = split(value, index);

  data_[index] = value;

  for (const auto& item : smaller)
    insert(item, left(index));

  for (const auto& item : bigger)
    insert(item, right(index));
}


template <class T>
auto FlatRbst<T>::split(const T& value, size_t index) -> PairOfVectors
{
  const auto iterate = [this](size_t index, const auto& f) {
    const auto iterate_impl = [this](size_t index, const auto& f, const auto& self) {
      if (!is_valid(index))
        return;

      f(data_[index]);
      self(left(index), f, self);
      self(right(index), f, self);
    };

    return iterate_impl(index, f, iterate_impl);
  };

  std::vector<T> smaller;
  std::vector<T> bigger;

  const auto parse = [&](/*optional<T>&*/ auto& item) {
    if (item < value)
      smaller.push_back(item->value);
    else if (value < item)
      bigger.push_back(item->value);
    item.reset();
  };

  iterate(index, parse);

  return {smaller, bigger};
}


template <class T> template <class Func>
void FlatRbst<T>::nlr_iterate(size_t index, Func f)
{
  if (!is_valid(index))
    return;

  f(data_[index]->value);

  nlr_iterate(left(index), f);
  nlr_iterate(right(index), f);
}

template <class T> template <class Func>
void FlatRbst<T>::lnr_iterate(size_t index, Func f)
{
  if (!is_valid(index))
    return;

  lnr_iterate(left(index), f);
  f(data_[index]->value);
  lnr_iterate(right(index), f);
}

template <class T> template <class Func>
void FlatRbst<T>::lrn_iterate(size_t index, Func f)
{
  if (!is_valid(index))
    return;

  lrn_iterate(left(index), f);
  lrn_iterate(right(index), f);
  f(data_[index]->value);
}

} // namespace Container

