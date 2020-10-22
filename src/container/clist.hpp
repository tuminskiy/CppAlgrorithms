#pragma once

#include <memory>
#include <utility>
#include <type_traits>
#include <cassert>

namespace Container {

template <class T>
struct CListNode; // forward declaration

template <class T>
using CListNodePtr = std::shared_ptr<CListNode<T>>;

template <class T>
struct CListNode
{
  explicit CListNode(T _value) : value(_value), prev(nullptr), next(nullptr) { }

  T value;
  CListNodePtr<T> prev;
  CListNodePtr<T> next;
};

template <class T>
auto make_clist_node(T&& arg)
{
  return std::make_shared<CListNode<std::decay_t<T>>>(std::forward<T>(arg));
}

template <class T>
class CList
{
  CListNodePtr<T> head_;
  CListNodePtr<T> tail_;
 
  size_t size_;

public:
  class Iterator
  {
    CListNodePtr<T> node_;

  public:
    explicit Iterator(CListNodePtr<T> node);
    
    Iterator& operator= (CListNodePtr<T> node);

    // prefix 
    Iterator& operator++ ();
    Iterator& operator-- ();

    // postfix
    Iterator operator++ (int);
    Iterator operator-- (int); 

    bool operator== (const Iterator& it);
    bool operator!= (const Iterator& it);
    T& operator* ();
  };

  explicit CList();
  ~CList() = default;

  size_t size() const;

  T& front();
  T& back();

  Iterator begin();
  Iterator end();

  void push_back(const T& value);
  void push_front(const T& value);

  void pop_back();
  void pop_front();

  T& operator[] (size_t index);

  void remove(size_t pos);

private:
  void init(const T& value);
};


// CList::Iterator
template <class T>
CList<T>::Iterator::Iterator(CListNodePtr<T> node) : node_(node) { }

template <class T>
typename CList<T>::Iterator& CList<T>::Iterator::operator= (CListNodePtr<T> node) { node_ = node; }

// prefix 
template <class T>
typename CList<T>::Iterator& CList<T>::Iterator::operator++ ()
{
  if (node_)
    node_ = node_->next;
  return *this;
}

template <class T>
typename CList<T>::Iterator& CList<T>::Iterator::operator-- ()
{
  if (node_)
    node_ = node_->prev;
  return *this;
}

// postfix
template <class T>
typename CList<T>::Iterator CList<T>::Iterator::operator++ (int)
{
  auto it = *this;
  ++*this;
  return it;
}

template <class T>
typename CList<T>::Iterator CList<T>::Iterator::operator-- (int)
{
  auto it = *this;
  --*this;
  return it;
}

template <class T>
bool CList<T>::Iterator::operator== (const CList<T>::Iterator& it) { return node_ == it.node_; }

template <class T>
bool CList<T>::Iterator::operator!= (const CList<T>::Iterator& it) { return node_ != it.node_; }

template <class T>
T& CList<T>::Iterator::operator* ()
{
  return node_->value;
}


// CList
template <class T>
CList<T>::CList() : head_(nullptr), tail_(nullptr), size_(0) { }

template <class T>
void CList<T>::init(const T& value)
{
  head_ = make_clist_node(value);
  tail_ = head_;

  head_->next = tail_;
  head_->prev = tail_;

  size_ = 1;
}

template <class T>
size_t CList<T>::size() const { return size_; }

template <class T>
T& CList<T>::front() { return head_->value; }

template <class T>
T& CList<T>::back() { return tail_->value; }

template <class T>
typename CList<T>::Iterator CList<T>::begin() { return Iterator(head_); }

template <class T>
typename CList<T>::Iterator CList<T>::end() { return Iterator(tail_); }

template <class T>
void CList<T>::push_back(const T& value)
{
  if (!head_) { init(value); }
  else {
    auto node = make_clist_node(value);

    node->next = head_;
    node->prev = tail_;

    tail_->next = node;
    tail_ = node;
    
    head_->prev = tail_;
    
    ++size_;
  }
}

template <class T>
void CList<T>::push_front(const T& value)
{
  if (!head_) { init(value); }
  else {
    auto node = make_clist_node(value);

    node->next = head_;
    node->prev = tail_;

    head_ = node;

    tail_->next = head_;
  
    ++size_;
  }
}

template <class T>
void CList<T>::pop_back()
{
  if (!head_) return;
  else if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    auto node = tail_->prev;
    
    node->next = head_;
    head_->prev = node;

    tail_ = node;
  }

  --size_;
}

template <class T>
void CList<T>::pop_front()
{
  if (!head_) return;
  else if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    auto node = head_->next;

    node->prev = tail_;
    tail_->next = node;

    head_ = node;
  }

  --size_;
}

template <class T>
T& CList<T>::operator[] (size_t index)
{
  assert(index < size_);

  auto node = head_;
  for (size_t i = 0; i < index; ++i)
    node = node->next;

  return node->value;
}

template <class T>
void CList<T>::remove(size_t pos)
{
  assert(pos < size_);

  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    auto node = head_;
    for (size_t i = 0; i < pos; ++i)
      node = node->next;

    node->prev->next = node->next;
    node->next->prev = node->prev; 
  }

  --size_;
}

} // namespace Container
