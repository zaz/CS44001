//
// node class template used to contruct lists
//
// Mikhail Nesterenko
// Modified by: Zaz Brown
//

#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:
  node(): next_(nullptr) {}

  ~node() {
    // do not destroy next_, since this will delete all further nodes
  }

  // functions can be inlined
  T getData() const {return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  std::shared_ptr<node<T>> getNext() const;
  void setNext(std::shared_ptr<node<T>> const);

private:
  T data_;
  std::shared_ptr<node<T>> next_;
};

//
// member functions for node
//
template <typename T>
std::shared_ptr<node<T>> node<T>::getNext() const {
  return next_;
}

template<typename T>
void node<T>::setNext(std::shared_ptr<node<T>> const next){
   next_ = next;
}

#endif // LIST_HPP_
