//
// Collection of nodes
//
// Zaz Brown
//

#include <iostream>
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

  // add a node to collection
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

  // XXX: What's a more succinct way to do this?
  // remove all nodes matching data from collection
  void remove(T data) {
    auto prev = head_;
    auto current = head_;
    // while not nullptr
    while (current) {
      if (current->getData() == data) {
        // if head
        if (current == head_) {
          head_ = head_->getNext();
          delete current;
          current = head_;
          prev = head_;
        } else {
          prev->setNext(current->getNext());
          delete current;
          current = prev->getNext();
        }
      } else {
        prev = current;
        current = current->getNext();
      }
    }
  }

  T last() { return tail_->getData(); }

  void print() {
    auto current = head_;
    // while not nullptr
    while (current) {
      std::cout << current->getData() << std::endl;
      current = current->getNext();
    }
  }

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
