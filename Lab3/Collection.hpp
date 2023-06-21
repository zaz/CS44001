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
  Collection() : head_(nullptr), tail_(nullptr) {}
  void add(T data) { tail_ = &data; }
  void remove(T data) { throw "remove() not implemented"; }
  void last() { throw "last() not implemented"; }
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
