#include <cmath>

#pragma once

#ifndef MY_ARRAY_H
#define MY_ARRAY_H

namespace s21 {

template <typename T, std::size_t N>
class Array {
 public:
  class ArrayIterator;
 private:
  // T defines the type of an element (T is template parameter)
  typedef T value_type;

  // T & defines the type of the reference to an element
  typedef T& reference;

  // const T & defines the type of the constant reference
  typedef const T& const_reference;

  // T * defines the type for iterating through the container
  typedef ArrayIterator iterator;

  // const T * defines the constant type for iterating through the container
  typedef const ArrayIterator const_iterator;

  // size_t defines the type of the container size (standard type is size_t)
  typedef size_t size_type;

  size_type _size = 0;

  value_type* _head = nullptr;

  void AllocMem(size_type size) {
    if (size != 0) {
      if (_head == nullptr) delete _head;
      _head = new value_type[size];
      _size = size;
    }
  }

 public:
  Array() { AllocMem(N); }

  Array(std::initializer_list<value_type> const& items) {
    AllocMem(N);
    int i = 0;
    for (value_type value : items) {
      if (i > N)
        throw std::out_of_range(
            "array costruct <initializer_list>: not enough space to fit other "
            "array in");
      _head[i] = value;
      i++;
    }
  }

  Array(const Array& other) {
    if (N < other._size)
      throw std::out_of_range(
          "array construct (arr other): not enough space to fit other array "
          "in");
    AllocMem(N);
    for (int i = 0; i < other._size; i++) {
      _head[i] = other._head[i];
    }
  }

  Array(Array&& other) {
    delete _head;
    _head = other._head;
    _size = other._size;

    other._head = nullptr;
    other._size = 0;
  }

  void operator=(Array&& other) {
    delete _head;
    _head = other._head;
    _size = other._size;

    other._head = nullptr;
    other._size = 0;
  }

  ~Array() {
    if (_head != nullptr) delete _head;
  }

  class ArrayIterator {
   private:
    value_type* _ptr;
    size_type _pos = 0;

   public:
    ArrayIterator() {}

    ArrayIterator(int pos, value_type* head) {
      _ptr = head;
      _pos = pos;
    }

    ArrayIterator(const_iterator& other) { *this = other; }

    bool operator==(const_iterator& other) {
      bool res = false;
      if (this->_pos == other._pos) res = true;
      return res;
    }

    bool operator!=(const_iterator& other) {
      bool res = false;
      if (this->_pos != other._pos) res = true;
      return res;
    }

    iterator operator++() {
      _pos++;
      return *this;
    }
    void operator=(const_iterator& other) {
      _ptr = other._ptr;
      _pos = other._pos;
    }

    iterator operator+(int num) {
      iterator temp(*this);
      for (int i = 0; i < num; i++, ++temp) {
      }
      return temp;
    }

    iterator operator++(int d) {
      _pos++;
      return *this;
    }
    iterator operator--() {
      _pos--;
      return *this;
    }
    iterator operator--(int d) {
      _pos--;
      return *this;
    }

    value_type operator*() { return _ptr[_pos]; }
  };

  // access specified element with bounds checking
  reference at(size_type pos) {
    if (pos >= _size)
      throw std::out_of_range("at : index is out of array range");
    return _head[pos];
  }

  // access specified element
  reference operator[](size_type pos) {
    if (pos >= _size)
      throw std::out_of_range("operator []: index is out of range");
    return _head[pos];
  }

  // access the first element
  const_reference front() { return *_head; }

  // access the last element
  const_reference back() { return _head[_size - 1]; }

  // direct access to the underlying array
  value_type* data() { return _head; }

  iterator begin() { return iterator(0, _head); }

  iterator end() { return iterator(_size, _head); }

  bool empty() { return (_head == nullptr); }

  size_type size() { return _size; }

  size_type max_size() { return _size; }

  void swap(Array& other) {
    value_type* swapH = _head;
    size_type swapS = other._size;
    _head = other._head;
    _size = other._size;
    other._head = swapH;
    other._size = swapS;
  }

  // assigns the given value value to all elements in the container.
  void fill(const_reference value) {
    for (int i = 0; i < _size; i++) {
      this->at(i) = value;
    }
  }
};

}  // namespace s21

#endif // MY_ARRAY_H