//
// Collection of nodes
//
// Zaz Brown
//

#include "list.hpp"

#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

template<typename T>
class Collection;

template<typename T>
bool equal(const Collection<T>&, const Collection<T>&);

// XXX: Should everything below be separated into a .cpp file?

template <typename T>
class Collection {
public:
  // TODO: check this does what I think it does
  Collection() : head_(nullptr), tail_(nullptr) {}

  void add(const T data) {
    auto newNode = new node<T>;
    newNode->setData(data);
    if (head_ == nullptr) {
      head_ = newNode;
      tail_ = newNode;
      return;
    }
    tail_->setNext(newNode);
    tail_ = newNode;
  }

  void remove(T data) { throw "remove() not implemented"; }

  T last() { return tail_->getData(); }

  void print() { throw "print() not implemented"; }

  friend bool equal<T>(const Collection&, const Collection&);

private:
  node<T> *head_;
  node<T> *tail_;
};

template<typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
  throw "equal() not implemented";
}

#endif // COLLECTION_HPP_
