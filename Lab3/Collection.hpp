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
    auto newNode = std::make_shared<node<T>>();
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
          current = head_;
          prev = head_;
        } else {
          prev->setNext(current->getNext());
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
      std::cout << current->getData() << ' ';
      current = current->getNext();
    }
    std::cout << std::endl;
  }

  friend bool equal<T>(const Collection&, const Collection&);

private:
  std::shared_ptr<node<T>> head_;
  std::shared_ptr<node<T>> tail_;
};

// return true if two collections contain the exact same elements
template<typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
  auto lhsCurrent = lhs.head_;
  auto rhsCurrent = rhs.head_;
  while (lhsCurrent && rhsCurrent) {
    if (lhsCurrent->getData() != rhsCurrent->getData()) {
      return false;
    }
    lhsCurrent = lhsCurrent->getNext();
    rhsCurrent = rhsCurrent->getNext();
  }
  // return false if one list is longer than the other
  return not(lhsCurrent || rhsCurrent);
}

#endif // COLLECTION_HPP_
