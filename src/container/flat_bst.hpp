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

private:
  std::vector<std::optional<T>> data_;

  size_t left(size_t parent) const;
  size_t right(size_t parent) const;
  size_t parent(size_t index) const;

  void insert(size_t index, const T& value);
};


template <class T>
void FlatBst<T>::insert(const T& value) { insert(0, value); }

template <class T>
void FlatBst<T>::insert(const std::initializer_list<T>& il)
{
  for (const auto& value : il)
    insert(value);
}


template <class T>
size_t FlatBst<T>::left(size_t parent) const { return parent * 2 + 1; }

template <class T>
size_t FlatBst<T>::right(size_t parent) const { return parent * 2 + 2; }

template <class T>
size_t FlatBst<T>::parent(size_t index) const { return (index - 1) / 2; }


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

} // namespace Container

