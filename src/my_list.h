#pragma once
#include <cmath>
#include <stdexcept>

#ifndef MY_LIST_H
#define MY_LIST_H

namespace s21 {
template <typename T>
class List {
 public:
  class ListIterator;

 private:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef ListIterator iterator;
  typedef const ListIterator const_iterator;
  typedef size_t size_type;

  struct Node {
    value_type _value;
    Node* _next = nullptr;
    Node* _prev = nullptr;
  };

  Node* _first = nullptr;
  Node* _end = nullptr;
  Node* _head = nullptr;

  int _size = 0;

  void InitList() {
    _first = new Node;
    _end = new Node;
    _first->_next = _end;
    _end->_prev = _first;
  }

 public:
  List() { this->InitList(); }

  // без префикса explicit т.к. в тестах используется конвертация из такой
  // конструкции: {double, double ,etc} в initializer list
  List(std::initializer_list<value_type> const& items) {
    this->InitList();
    for (value_type value : items) {
      this->push_back(value);
      _size++;
    }
  }

  List(List const& other) { *this = other; }

  explicit List(size_type size) {
    InitList();
    for (int i = 0; i < size; i++) {
      push_back();
    }
    _size = size;
  }

  List(List&& other) {
    this->clear();
    _head = other._head;
    _first = other._first;
    _end = other._end;
    _size = other._size;

    other._head = nullptr;
    other._first = nullptr;
    other._end = nullptr;
    other._size = 0;
  }

  ~List() {
    Node* r = _first;
    if (r != nullptr) {
      // delete _end;
      while (r != nullptr) {
        Node* temp = r;
        r = r->_next;
        delete temp;
      }
      _head = nullptr;
      _size = 0;
    }
  }

  void operator=(List const& other) {
    this->clear();
    this->InitList();
    Node* r = other._head;
    while (r != other._end) {
      push_back(r->_value);
      r = r->_next;
    }

    _size = other._size;
  }

  void operator=(List&& other) {
    this->clear();
    this->InitList();
    Node* r = other._head;
    while (r != other._end) {
      push_back(r->_value);
      r = r->_next;
    }
    _size = other._size;
    other.clear();
  }

  /// methods

  iterator insert(iterator pos, const_reference value) {
    Node* ptr = pos.GetPointer();
    if (ptr == nullptr)
      throw std::out_of_range("insert : iterator point to null");
    Node* elemNew = new Node;
    elemNew->_value = value;
    elemNew->_next = ptr;
    elemNew->_prev = ptr->_prev;
    ptr->_prev->_next = elemNew;
    ptr->_prev = elemNew;
    if (ptr == _head) _head = elemNew;
    _size++;
    return iterator(--pos);
  }

  void erase(iterator pos) {
    Node *ptr = pos.GetPointer(), *del;
    if (ptr == nullptr)
      throw std::out_of_range("insert : iterator point to null");
    if (ptr == _head) {
      _head = ptr->_next;
      del = ptr;
      ptr->_prev->_next = ptr->_next;
      ptr->_next->_prev = ptr->_prev;
    } else {
      del = ptr;
      ptr->_prev->_next = ptr->_next;
      ptr->_next->_prev = ptr->_prev;
    }
    _size--;
    if (_size == 0) _head = nullptr;
    delete del;
  }

  void pop_back() {
    if (!this->empty()) {
      List<value_type>::iterator end = this->end();
      --end;
      this->erase(end);
    }
  }

  void pop_front() {
    if (!this->empty()) {
      List<value_type>::iterator begin = this->begin();
      this->erase(begin);
    }
  }

  void swap(List& other) {
    Node *swapH = _head, *swapE = _end, *swapF = _first;
    int swapS = _size;
    _head = other._head;
    _end = other._end;
    _first = other._first;
    _size = other._size;
    other._head = swapH;
    other._end = swapE;
    other._first = swapF;
    other._size = swapS;
  }

  void merge(List& other) {
    List<value_type>::iterator iter = other.begin(), end = other.end();
    for (; iter != end; ++iter) {
      this->push_back(*iter);
    }
  }

  void splice(const_iterator pos, List& other) {
    List<value_type>::iterator end = other.end(), iter = other.begin(),
                               temp = pos;
    for (; iter != end; ++iter) {
      insert(pos, *iter);
    }
  }

  void reverse() {
    List<value_type> newList;
    List<value_type>::iterator iter = this->end(), start = this->begin();
    --start;
    --iter;
    for (; iter != start; --iter) {
      newList.push_back(*iter);
    }
    *this = newList;
  }

  void unique() {
    List<value_type>::iterator iter = this->begin(), end = this->end();
    for (; iter != end; ++iter) {
      bool uniq = true;
      for (List<value_type>::iterator iter2 = iter + 1; uniq && iter2 != end;
           ++iter2) {
        if (*iter2 == *iter) {
          --iter;
          uniq = false;
          this->erase(iter2);
        }
      }
    }
  }

  void sort();

  void push_back() {
    if (_first == nullptr) {
      this->InitList();
    }
    Node* elemNew = new Node;
    if (_head == nullptr) {
      _head = elemNew;
      _head->_prev = _first;
      _head->_next = _end;
      _first->_next = _head;
      _end->_prev = _head;
    } else {
      Node* last = _end->_prev;
      elemNew->_prev = last;
      elemNew->_next = _end;
      last->_next = elemNew;
      _end->_prev = elemNew;
    }
  }

  void push_back(value_type value) {
    if (_first == nullptr) {
      this->InitList();
    }
    Node* elemNew = new Node;
    elemNew->_value = value;
    if (_head == nullptr) {
      _head = elemNew;
      _head->_prev = _first;
      _head->_next = _end;
      _first->_next = _head;
      _end->_prev = _head;
    } else {
      Node* last = _end->_prev;
      elemNew->_prev = last;
      elemNew->_next = _end;
      last->_next = elemNew;
      _end->_prev = elemNew;
    }
  }

  void push_front(value_type value) {
    if (_first == nullptr) {
      this->InitList();
    }
    Node* elemNew = new Node;
    elemNew->_value = value;
    if (_head == nullptr) {
      _head = elemNew;
      _head->_prev = _first;
      _head->_next = _end;
      _first->_next = _head;
      _end->_prev = _head;
    } else {
      elemNew->_next = _head;
      elemNew->_prev = _first;
      _first->_next = elemNew;
      _head->_prev = elemNew;
      _head = elemNew;
    }
  }

  bool empty() {
    bool res = false;
    if (_head == nullptr) {
      res = true;
    }
    return res;
  }

  const_reference back() {
    if (this->empty() == false) {
      return _end->_prev->_value;
    }
    return _end->_value;
  }

  const_reference front() {
    if (this->empty() == false) {
      return _head->_value;
    }
    return _first->_value;
  }

  void clear() {
    Node* ptr = _first;
    while (ptr != nullptr) {
      Node* del = ptr;
      ptr = ptr->_next;
      delete del;
    }
    _head = nullptr;
    _first = nullptr;
    _end = nullptr;
    _size = 0;
  }

  size_type size() { return _size; }

  size_type max_size() { return pow(2, 32) - 1; }

  /// iterators

  class ListIterator {
   private:
    Node* _ptr = nullptr;
    int _pos = 0;

   public:
    ListIterator() {}
    ListIterator(Node* ptr, int pos) {
      _ptr = ptr;
      _pos = pos;
    }

    ListIterator(const_iterator& other) {
      _ptr = other._ptr;
      _pos = other._pos;
    }

    void operator=(const_iterator other) {
      _ptr = other._ptr;
      _pos = other._pos;
    }

    bool operator!=(const_iterator other) {
      bool res = false;
      if (_ptr != other._ptr) res = true;
      return res;
    }

    bool operator==(const_iterator other) {
      bool res = true;
      if (_ptr != other._ptr) res = false;
      return res;
    }

    iterator operator++() {
      if (_ptr == nullptr) {
        throw std::out_of_range(
            "operator ++: iterator is pointing to null element");
      }
      _ptr = _ptr->_next;
      _pos++;
      return *this;
    }
    iterator operator++(int ghost) {
      if (_ptr == nullptr) {
        throw std::out_of_range(
            "operator ++: iterator is pointing to null element");
      }
      _ptr = _ptr->_next;
      _pos++;
      return *this;
    }

    iterator operator--() {
      if (_ptr == nullptr) {
        throw std::out_of_range(
            "operator --: iterator is pointing to null element");
      }
      _ptr = this->_ptr->_prev;
      _pos--;
      return *this;
    }

    iterator operator--(int ghost) {
      if (_ptr == nullptr) {
        throw std::out_of_range(
            "operator --: iterator is pointing to null element");
      }
      _ptr = this->_ptr->_prev;
      _pos--;
      return *this;
    }

    iterator operator-(int number) {
      iterator ret = *this;
      if (number < 0) {
        ret = *this - number;
      }
      for (int i = 0; i < number; i++) {
        if (ret._ptr == nullptr) {
          throw std::out_of_range(
              "operator *: iterator is pointing to null element");
        }
        ret._ptr = this->_ptr->_prev;
        ret._pos--;
      }
      return ret;
    }

    iterator operator+(int number) {
      iterator ret = *this;
      if (number < 0) {
        *this = *this - number;
      }
      for (int i = 0; i < number; i++) {
        if (ret._ptr == nullptr) {
          throw std::out_of_range(
              "operator *: iterator is pointing to null element");
        }
        ret._ptr = ret._ptr->_next;
        ret._pos++;
      }
      return ret;
    }

    reference operator*() {
      if (_ptr == nullptr) {
        throw std::out_of_range(
            "operator *: iterator is pointing to null element");
      }
      return _ptr->_value;
    }

    Node* GetPointer() { return _ptr; }
  };
  iterator begin() {
    iterator ret(_head, 0);
    return ret;
  }
  iterator end() {
    iterator ret(_end, _size);
    return ret;
  }

  /// auxiliary
  void show() {
    for (Node* temp = _head; temp != _end; temp = temp->_next) {
      std::cout << temp->_value << std::endl;
    }
  }

  /// bonus

  /// inserts new elements into the container directly before pos
  void emplace(iterator pos) {}

  template <class Type, class... Args>
  void emplace(iterator it, Type value, Args... args) {
    insert(it, value);
    emplace(it, args...);
  }

  // // appends new elements to the end of the container

  void emplace_back() {}
  template <class Type, class... Args>
  void emplace_back(Type value, Args... args) {
    push_back(value);
    emplace_back(args...);
  }

  // appends new elements to the top of the container
  void emplace_front() {}
  template <class Type, class... Args>
  void emplace_front(Type value, Args... args) {
    emplace(this->begin(), value, args...);
  }
};

}  // namespace s21

#endif // MY_LIST_H