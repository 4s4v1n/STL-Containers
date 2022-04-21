#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <string>
#include <memory>

namespace s21 {
template<typename Type>
class Vector {
 public:

  class VectorIterator {
   public:

    VectorIterator() {}

    VectorIterator(const VectorIterator &other) {
      Pointer = other.Pointer;
      Position = other.Position;
    }

    ~VectorIterator() {}

    void SetIterator(std::shared_ptr<Type[]> InitPointer) {Pointer = InitPointer;}

    Type &operator*() {return Pointer[Position];}

    void operator++() {Position += 1;}

    void operator--() {Position -= 1;}

    void operator=(const VectorIterator other) {
      copy(other);
      Pointer = other.Pointer;
    }

    bool operator==(const VectorIterator other) {return Position == other.Position;}

    bool operator!=(const VectorIterator other) {return Position != other.Position;}

    bool operator>=(const VectorIterator other) {return Position >= other.Position;}

    bool operator<=(const VectorIterator other) {return Position <= other.Position;}

    void Advance(size_t repeat) {Position += repeat;}

    void Decrease(size_t repeat) {Position -= repeat;}

    const size_t GetPosition() {return Position;}

    void swap(VectorIterator &other) {
      Pointer.swap(other.Pointer);
      std::swap(Position, other.Position);
    }

    void copy(const VectorIterator other) {Position = other.Position;}

   private:
    std::shared_ptr<Type[]> Pointer;
    size_t Position{0};
  };

  typedef size_t size_type;
  typedef Type value_type;
  typedef Type &reference;
  typedef Type &const_reference;
  typedef VectorIterator iterator;
  typedef const VectorIterator const_iterator;
  //  Vector constructors

  Vector() {
    BeginIterator.SetIterator(Store);
    EndIterator.SetIterator(Store);
  }

  Vector(const size_type NewSize) {
    Store.reset(new Type[NewSize]{});
    VectorMaxSize = NewSize;
    BeginIterator.SetIterator(Store);
    EndIterator.SetIterator(Store);
  }

  Vector(const Vector &other) {
    VectorSize = other.VectorSize;
    VectorMaxSize = other.VectorMaxSize;
    Store.reset(new Type[VectorMaxSize]{});
    for (int i{0}; i < VectorSize; i++) {
      Store[i] = other.Store[i];
    }
    BeginIterator.SetIterator(Store);
    BeginIterator.copy(other.BeginIterator);
    EndIterator.SetIterator(Store);
    EndIterator.copy(other.EndIterator);
  }

  Vector(std::initializer_list<value_type> const &items) {
    VectorSize = items.size();
    VectorMaxSize = VectorSize;
    Store.reset(new Type[VectorSize]{});
    BeginIterator.SetIterator(Store);
    EndIterator.SetIterator(Store);
    auto iter{items.begin()};
    Store[0] = *iter;
    iter++;
    for (int i{1}; iter != items.end(); i++, iter++) {
      Store[i] = *iter;
      ++EndIterator;
    }
  }

  Vector(Vector &&other) {swap(other);}

  //  Vector methods

  void push_back(value_type value);

  void pop_back();

  void shrink_to_fit();

  void reserve(size_type NewSize);

  void swap(Vector& other);

  const_reference front();

  const_reference back();

  reference at(size_type pos);

  iterator begin() {return BeginIterator;}

  iterator end() {return EndIterator;}

  reference operator[](size_type pos) {return Store[pos];}

  iterator insert(iterator pos, const_reference value);

  void operator=(Vector &&other );

  //  capacity methods

  bool empty() {
    bool Emptiness{false};
    if (VectorSize == 0) {
      Emptiness = true;
    }
    return Emptiness;
  }

  size_type size() {return VectorSize;}

  size_type max_size() {return VectorMaxSize;}

  size_type capacity() {return VectorMaxSize - VectorSize;}

  void SizeIncrement() {VectorSize++;}

  void MaxSizeIncrement() {VectorMaxSize++;}

  void clear();

  void ResetPointer(std::shared_ptr<Type[]> newPointer);

  void erase(iterator position);

  std::shared_ptr<Type[]> data() {return Store;}

  iterator emplace(const_iterator pos) {return pos;}

  template <class T, class... Args>
  iterator emplace(const_iterator pos, T data, Args... args) {
    iterator real_pos{insert(pos, data)};
    real_pos = emplace(real_pos, args...);
    return real_pos;
  }

  void emplace_back() {}
  template <class T, class... Args>
  void emplace_back(T data, Args... args) {
    push_back(data);
    emplace_back(args...);
  }

 private:
  std::shared_ptr<Type[]> Store{new Type[0]{}};
  iterator BeginIterator;
  iterator EndIterator;
  size_type VectorSize{0};
  size_type VectorMaxSize{0};

  void IncreaseStoreAllocation(const Vector &old) {
    std::shared_ptr<Type[]> store{new Type[VectorMaxSize]{}};
    for (size_t i{0}; i < VectorSize; i++) {
      store[i] = old.Store[i];
    }
    Store = std::move(store);
    BeginIterator.SetIterator(Store);
    EndIterator.SetIterator(Store);
  }

  void DecreaseStoreAllocation(const Vector &old) {
    std::shared_ptr<Type[]> store{new Type[VectorMaxSize]{}};
    for (size_t i{0}; i < VectorSize; i++) {
      store[i] = old.Store[i];
    }
    Store = std::move(store);
  }
};


template<typename Type>
void Vector<Type>::push_back(value_type value) {
  if (!empty()) {
    ++EndIterator;
  }
  if (VectorSize >= VectorMaxSize) {
    VectorMaxSize += 1;
    IncreaseStoreAllocation(*this);
  }
  VectorSize += 1;
  *EndIterator = value;
}

template<typename Type>
void Vector<Type>::shrink_to_fit() {
  if (VectorSize < VectorMaxSize) {
    DecreaseStoreAllocation(*this);
    VectorMaxSize = VectorSize;
  }
}

template<typename Type>
void Vector<Type>::reserve(size_type NewSize) {
      VectorMaxSize += NewSize;
      IncreaseStoreAllocation(*this);
    }

template<typename Type>
void Vector<Type>::swap(Vector& other) {
  Store.swap(other.Store);
  std::swap(VectorSize, other.VectorSize);
  std::swap(VectorMaxSize, other.VectorMaxSize);
  BeginIterator.swap(other.BeginIterator);
  EndIterator.swap(other.EndIterator);
}

template<typename Type>
void Vector<Type>::clear() {
  while (EndIterator != BeginIterator) {
    *EndIterator = 0;
    --EndIterator;
  }
  VectorSize = 0;
  VectorMaxSize = 0;
  Store.reset(new Type[0]{});
  EndIterator.SetIterator(Store);
  BeginIterator.SetIterator(Store);
}

template<typename Type>
void Vector<Type>::ResetPointer(std::shared_ptr<Type[]> newPointer) {
  Store = newPointer;
  BeginIterator.SetIterator(Store);
  EndIterator.SetIterator(Store);
}

template<typename Type>
void Vector<Type>::erase(iterator position) {
  *position = 0;
  --EndIterator;
  for (size_t i{0}, j{0}; i < VectorSize; i++, j++) {
    if (i == position.GetPosition()) {
      j++;
    }
    Store[i] = Store[j];
  }
  VectorSize -= 1;
}

template<typename Type>
void Vector<Type>::operator=(Vector &&other ) {
  VectorSize = other.VectorSize;
  VectorMaxSize = other.VectorMaxSize;
  Store.reset(new Type[VectorMaxSize]{});
  for (int i{0}; i < VectorSize; i++) {
    Store[i] = other.Store[i];
  }
  BeginIterator.SetIterator(Store);
  BeginIterator.copy(other.BeginIterator);
  EndIterator.SetIterator(Store);
  EndIterator.copy(other.EndIterator);
}


template<typename Type>
typename Vector<Type>::iterator Vector<Type>::insert(iterator pos, const_reference value) {
size_type InsertPosition = pos.GetPosition();
  VectorSize += 1;
  if (VectorSize >= VectorMaxSize) {
    VectorMaxSize += 1;
    IncreaseStoreAllocation(*this);
  }
  std::shared_ptr<value_type[]> store{new value_type[VectorMaxSize]};
  if (InsertPosition < VectorSize - 1) {
    VectorIterator access(begin());
    for (size_t i{0}, j{0}; i < VectorSize - 1; i++, j++) {
    if (j == InsertPosition) {
      store[j] = value;
      j++;
    }
      store[j] = *access;
      ++access;
    }
    Store = std::move(store);
    BeginIterator.SetIterator(Store);
    EndIterator.SetIterator(Store);
  } else {
    *EndIterator = value;
  }
  ++EndIterator;
  VectorIterator InsertedPositionIterator;
  InsertedPositionIterator.SetIterator(Store);
  InsertedPositionIterator.Advance(InsertPosition);
  return InsertedPositionIterator;
}

template<typename Type>
void Vector<Type>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Не туда воюешь!");
  }
  *EndIterator = 0;
  VectorSize -= 1;
  *EndIterator = 0;
  --EndIterator;
}

template<typename Type>
typename Vector<Type>::const_reference Vector<Type>::front() {
  if (empty())  {
    throw std::out_of_range("Не туда воюешь!");
  }
  return *BeginIterator;
}

template<typename Type>
typename Vector<Type>::const_reference Vector<Type>::back() {
  if (empty())  {
    throw std::out_of_range("Не туда воюешь!");
  }
  return *EndIterator;
}

template<typename Type>
typename Vector<Type>::reference Vector<Type>::at(size_type pos) {
  if (pos < 0 && pos > VectorSize) {
    throw std::out_of_range("Не туда воюешь!");
  }
  return Store[pos];
}


}

#endif // MY_VECTOR_H
