#ifndef MY_CONTAINERADAPTOR_H
#define MY_CONTAINERADAPTOR_H

#include <memory>
#include <initializer_list>
#include <iostream>

namespace s21 {
template<typename Type>
class ContainerAdaptor {
 public:
  typedef size_t size_type;
  typedef Type value_type;
  typedef Type &reference;
  typedef Type &const_reference;

  ContainerAdaptor() {
  }

  ContainerAdaptor(std::initializer_list<value_type> const &items) {
    Position = items.size() - 1;
    Store.reset(new Type[items.size()]{});
    auto iter{items.begin()};
    for (int i{0}; iter != items.end(); i++, iter++) {
      GetStore(i) = *iter;
    }
  }

  ContainerAdaptor(const ContainerAdaptor &old) {
    Position = old.Position;
    ReallocateStoreAfterPush(old);
  }

  ContainerAdaptor(ContainerAdaptor &&old) {
    Position = old.Position;
    Store.swap(old.Store);
    old.Position = -1;
  }

  ~ContainerAdaptor() {
  }

  void push(Type &value);

  bool empty();

  void swap(ContainerAdaptor &other);

  void operator=(ContainerAdaptor &&old);

  size_type size() {return Position + 1;}

  //  auxiliary methods

  Type& GetStore(int pos) {return Store[pos];};

  int GetPosition() {return Position;}

  void DecreasePosition() {Position -= 1;}

 protected:

  void ReallocateStoreAfterPush(const ContainerAdaptor &old);

  void ReallocateStoreAfterPop(const ContainerAdaptor &old);

 private:
  int Position{-1};
  std::unique_ptr<Type[]> Store{new Type[1]{}};
};

template<typename Type>
class Stack : public ContainerAdaptor<Type> {
  using ContainerAdaptor<Type>::ContainerAdaptor;
 public:
  void pop() {
    if (ContainerAdaptor<Type>::empty()) {
      throw std::out_of_range("No such element");
    }
    top() = 0;
    ContainerAdaptor<Type>::DecreasePosition();
  }

  ContainerAdaptor<Type>::reference top() {
    if (ContainerAdaptor<Type>::empty()) {
      throw std::out_of_range("No such element");
    }
    return ContainerAdaptor<Type>::GetStore(ContainerAdaptor<Type>::GetPosition());
  }

  void emplace_front() {}
  template <class T, class... Args>
  void emplace_front(T data, Args... args) {
    ContainerAdaptor<Type>::push(data);
    emplace_front(args...);
  }
 private:
};

template<typename Type>
class Queue : public ContainerAdaptor<Type> {
  using ContainerAdaptor<Type>::ContainerAdaptor;
 public:
  ContainerAdaptor<Type>::reference front() {
    if (ContainerAdaptor<Type>::empty()) {
      throw std::out_of_range("No such element");
    }
    return ContainerAdaptor<Type>::GetStore(0);
  }

  ContainerAdaptor<Type>::reference back() {
    if (ContainerAdaptor<Type>::empty()) {
      throw std::out_of_range("No such element");
    }
    return ContainerAdaptor<Type>::GetStore(ContainerAdaptor<Type>::GetPosition());
  }

  void emplace_back() {}
  template <class T, class... Args>
  void emplace_back(T data, Args... args) {
    ContainerAdaptor<Type>::push(data);
    emplace_back(args...);
  }

  void pop() {
    if (ContainerAdaptor<Type>::empty()) {
      throw std::out_of_range("No such element");
    }
    front() = 0;
    ContainerAdaptor<Type>::DecreasePosition();
    ContainerAdaptor<Type>::ReallocateStoreAfterPop(*this);
  }
 private:
};

template<typename Type>
void ContainerAdaptor<Type>::operator=(ContainerAdaptor &&old) {
  Position = old.Position;
  ReallocateStoreAfterPush(old);
}

template<typename Type>
void ContainerAdaptor<Type>::swap(ContainerAdaptor &other){
  std::swap(Position, other.Position);
  Store.swap(other.Store);
}


template<typename Type>
void ContainerAdaptor<Type>::push(Type &value) {
    Position += 1;
    ReallocateStoreAfterPush(*this);
    Store[Position] = value;
  }


template<typename Type>
bool ContainerAdaptor<Type>::empty() {
    bool result = false;
    if (Position < 0) {
      result = true;
    }
    return result;
  }


template<typename Type>
void ContainerAdaptor<Type>::ReallocateStoreAfterPush(const ContainerAdaptor &old) {
    std::unique_ptr<Type[]> store{new Type[Position+1]{}};
    for (int i{0}; i <= Position; i++) {
      store[i] = old.Store[i];
    }
    Store = std::move(store);
  }


template<typename Type>
void ContainerAdaptor<Type>::ReallocateStoreAfterPop(const ContainerAdaptor &old) {
    std::unique_ptr<Type[]> store{new Type[Position+1]{}};
    for (int i{Position}, j{Position + 1}; i >= 0; i--, j--) {
      store[i] = old.Store[j];
    }
    Store = std::move(store);
  }
}



#endif // MY_CONTAINERADAPTOR_H
