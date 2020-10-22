#pragma once

#include <cstddef> // size_t
#include <cassert> // assert

namespace Container {

template <class T>
struct CListNode
{
  explicit CListNode(T _value);

  T value;
  CListNode* prev;
  CListNode* next;
};


template <class T>
class CList
{
  CListNode<T>* root_;
  std::size_t size_;

public:
  class Iterator
  {
    friend class CList;

    const CList<T>* parent_;
    CListNode<T>* node_;

    explicit Iterator(const CList<T>* parent, CListNode<T>* node);

  public:

    bool operator!= (const Iterator& it) const;

    T& operator* ();
    T* operator-> ();

    // prefix
    Iterator& operator++();
    Iterator& operator--();

    // postfix
    Iterator operator++(int);
    Iterator operator--(int);

    Iterator& operator+= (std::size_t value);
    Iterator& operator-= (std::size_t value);

    Iterator operator+ (std::size_t value);
    Iterator operator- (std::size_t value);
  };

  explicit CList();
  ~CList();

  std::size_t size() const;

  void push_back(const T& value);
  void push_front(const T& value);

  void pop_back();
  void pop_front();

  T& operator[] (std::size_t index);

  T& front();
  T& back();

  Iterator begin();
  Iterator end();

  Iterator insert(Iterator it, const T& value);
  void erase(Iterator it);
};


// CListNode
template <class T>
CListNode<T>::CListNode(T _value) : value(_value) { }


// CList::Iterator
template <class T>
CList<T>::Iterator::Iterator(const CList<T>* parent, CListNode<T>* node)
  : parent_(parent), node_(node) { }

template <class T>
bool CList<T>::Iterator::operator!= (const CList<T>::Iterator& it) const { return node_ != it.node_; }

template <class T>
T& CList<T>::Iterator::operator* () { return node_->value; }

template <class T>
T* CList<T>::Iterator::operator-> () { return &(operator*()); }

// prefix
template <class T>
typename CList<T>::Iterator& CList<T>::Iterator::operator++ ()
{
  if (node_) {
    node_ = node_->next;

    auto first = parent_->root_;
    if (node_ == first)
      node_ = nullptr;
  }

  return *this;
}

template <class T>
typename CList<T>::Iterator& CList<T>::Iterator::operator-- ()
{
  auto last = parent_->root_->prev;

  if (node_) {
    node_ = node_->prev;
    if (node_ == last)
      node_ = nullptr;
  } else {
    node_ = last;
  }

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
typename CList<T>::Iterator& CList<T>::Iterator::operator+= (std::size_t value)
{
  if (node_)
    for(size_t i = 0; i < value; ++i)
      ++*this;

  return *this;
}

template <class T>
typename CList<T>::Iterator& CList<T>::Iterator::operator-= (std::size_t value)
{
  for (std::size_t i = 0; i < value; i++)
    --*this;

  return *this;
}

template <class T>
typename CList<T>::Iterator CList<T>::Iterator::operator+ (std::size_t value)
{
  return Iterator(*this) += value;
}

template <class T>
typename CList<T>::Iterator CList<T>::Iterator::operator- (std::size_t value)
{
  return Iterator(*this) -= value;
}


// CList
template <class T>
CList<T>::CList() : root_(nullptr), size_(0) { }

template <class T>
CList<T>::~CList<T>()
{
  if (size_ != 0) {
    auto node = root_;

    while (node->next != root_) {
      auto tmp = node;
      node = node->next;
      delete tmp;
    }

    delete node;
  }
}

template <class T>
std::size_t CList<T>::size() const { return size_; }

template <class T>
void CList<T>::push_back(const T& value)
{
  auto node = new CListNode<T>(value);

  if (!root_) {
    root_ = node;
    root_->prev = node;
    root_->next = node;
  } else {
    node->prev = root_->prev;
    node->next = root_;

    root_->prev->next = node;
    root_->prev = node;
  }

  ++size_;
}

template <class T>
void CList<T>::push_front(const T& value)
{
  auto node = new CListNode<T>(value);

  if (!root_) {
    root_ = node;
    root_->prev = node;
    root_->next = node;
  } else {
    node->prev = root_->prev;
    node->next = root_;

    root_->prev->next = node;
    root_ = node;
  }

  ++size_;
}

template <class T>
void CList<T>::pop_back()
{
	if (!root_) return;

  if (size_ == 1) delete root_;
  else {
  	auto last = root_->prev;

  	last->prev->next = root_;
  	root_->prev = last->prev;

  	delete last;
	}

  --size_;
}

template <class T>
void CList<T>::pop_front()
{
	if (!root_) return;

  if (size_ == 1) delete root_;
  else {
  	auto last = root_->prev;
		auto node = root_->next;

  	node->prev = last;
  	last->next = node;

  	delete root_;

  	root_ = node;
	}

  --size_;
}

template <class T>
T& CList<T>::operator[] (std::size_t index)
{
	assert(index < size_);

  auto node = root_;
  for (std::size_t i = 0; i < index; ++i)
    node = node->next;

  return node->value;
}

template <class T>
T& CList<T>::front() { return root_->value; }

template <class T>
T& CList<T>::back() { return root_->prev->value; }

template <class T>
typename CList<T>::Iterator CList<T>::begin() { return Iterator(this, root_); }

template <class T>
typename CList<T>::Iterator CList<T>::end() { return Iterator(this, nullptr); }

template <class T>
typename CList<T>::Iterator CList<T>::insert(CList<T>::Iterator it, const T& value)
{
	auto node = new CListNode<T>(value);

  node->prev = it.node_;
  node->next = it.node_->next;

  if (size_ != 1)
    it.node_->next->prev = node;
	it.node_->next = node;

  if (size_ == 1)
    it.node_->prev = node;

  ++size_;

  return Iterator(this, node);
}

template <class T>
void CList<T>::erase(CList<T>::Iterator it)
{
  it.node_->prev->next = it.node_->next;
  it.node_->next->prev = it.node_->prev;

  delete it.node_;
}

} // namespace Container
