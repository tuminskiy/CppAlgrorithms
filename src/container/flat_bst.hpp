#pragma once

#include <vector>
#include <optional>

namespace Container {

template <class T>
class FlatBst
{
public:
  virtual ~FlatBst() = default;

  void insert(const T& value);
  void insert(const std::initializer_list<T>& il);

  template <class Func> void nlr_iterate(Func f);
  template <class Func> void lnr_iterate(Func f);
  template <class Func> void lrn_iterate(Func f);

private:
  std::vector<std::optional<T>> data_;

  size_t left(size_t parent) const;
  size_t right(size_t parent) const;
  size_t parent(size_t index) const;

  bool is_valid(size_t index) const;

  void insert(size_t index, const T& value);

  template <class Func> void nlr_iterate(size_t index, Func f);
  template <class Func> void lnr_iterate(size_t index, Func f);
  template <class Func> void lrn_iterate(size_t index, Func f);
};


template <class T>
void FlatBst<T>::insert(const T& value) { insert(0, value); }

template <class T>
void FlatBst<T>::insert(const std::initializer_list<T>& il)
{
  for (const auto& value : il)
    insert(value);
}


template <class T> template <class Func>
void FlatBst<T>::nlr_iterate(Func f) { return nlr_iterate(0, f); }

template <class T> template <class Func>
void FlatBst<T>::lnr_iterate(Func f) { return lnr_iterate(0, f); }

template <class T> template <class Func>
void FlatBst<T>::lrn_iterate(Func f) { return lrn_iterate(0, f); }


template <class T>
size_t FlatBst<T>::left(size_t parent) const { return parent * 2 + 1; }

template <class T>
size_t FlatBst<T>::right(size_t parent) const { return parent * 2 + 2; }

template <class T>
size_t FlatBst<T>::parent(size_t index) const { return (index - 1) / 2; }


template <class T>
bool FlatBst<T>::is_valid(size_t index) const
{
  return index < data_.size() && data_[index];
}


template <class T>
void FlatBst<T>::insert(size_t index, const T& value)
{
  if (data_.size() <= index)
    data_.resize(index + 1);

  if (!data_[index])
    data_[index] = value;
  else if (value < data_[index])
    insert(left(index), value);
  else if (data_[index] < value)
    insert(right(index), value);
}


template <class T> template <class Func>
void FlatBst<T>::nlr_iterate(size_t index, Func f)
{
  if (!is_valid(index))
    return;

  f(data_[index].value());

  nlr_iterate(left(index), f);
  nlr_iterate(right(index), f);
}

template <class T> template <class Func>
void FlatBst<T>::lnr_iterate(size_t index, Func f)
{
  if (!is_valid(index))
    return;

  lnr_iterate(left(index), f);
  f(data_[index].value());
  lnr_iterate(right(index), f);
}

template <class T> template <class Func>
void FlatBst<T>::lrn_iterate(size_t index, Func f)
{
  if (!is_valid(index))
    return;

  lrn_iterate(left(index), f);
  lrn_iterate(right(index), f);
  f(data_[index].value());
}

} // namespace Container

