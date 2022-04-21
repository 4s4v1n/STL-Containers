#ifndef MY_MULTISET_H
#define MY_MULTISET_H

#include "my_set.h"

namespace s21 {

template <class Key>
class multiset : protected set<Key> {
 private:
  typedef Key key_type;
  typedef key_type value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

 public:
  class MultisetIterator : protected set<Key>::SetIterator {
   private:
    friend class multiset;
    BST_Node* _IncreaseIterator(BST_Node* tree, BST_Node* changeNode);
    BST_Node* _DecreaceIterator(BST_Node* tree, BST_Node* changeNode);
    bool _fake;

   public:
    MultisetIterator() {
      this->_node = nullptr;
      _fake = false;
    }
    ~MultisetIterator() {
      if (_fake && this->_node != nullptr) delete this->_node;
      this->_node = nullptr;
      _fake = false;
    }
    value_type operator*() { return set<value_type>::iterator::operator*(); }
    void operator=(const MultisetIterator& other) {
      if (*this != other) {
        if (this->_fake) {
          delete this->_node;
        }
        this->_node = other._node;
        this->_fake = other._fake;
      }
    }
    bool operator==(const MultisetIterator& other) {
      return set<value_type>::iterator::operator==(other);
    }
    bool operator!=(const MultisetIterator& other) {
      return set<value_type>::iterator::operator!=(other);
    }
    void operator++() {
      this->_node = _IncreaseIterator(this->_node, this->_node);
    }
    void operator--() {
      this->_node = _DecreaceIterator(this->_node, this->_node);
    }
  };  // MultisetIterator

  typedef MultisetIterator iterator;
  typedef const MultisetIterator const_iterator;

  // Member functions
  multiset() {}
  explicit multiset(std::initializer_list<value_type> const& items) {
    for (auto& item : items) {
      this->insert(item);
    }
  }
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset() {}
  void operator=(multiset&& ms);

  // Iterator
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator& pos);
  void swap(multiset&& other);
  void merge(multiset& other);

  // Lookup
  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  // Emplace
  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args);
  std::vector<std::pair<iterator, bool>> emplace();
};
}  // namespace s21

template <class value_type>
typename s21::BST<value_type>::Node*
s21::multiset<value_type>::iterator::_IncreaseIterator(BST_Node* tree,
                                                       BST_Node* changeNode) {
  return set<value_type>::iterator::_IncreaseIterator(tree, changeNode);
}

template <class value_type>
typename s21::BST<value_type>::Node*
s21::multiset<value_type>::iterator::_DecreaceIterator(BST_Node* tree,
                                                       BST_Node* changeNode) {
  return set<value_type>::iterator::_DecreaceIterator(tree, changeNode);
}

// Member function
// -----------------------------------------------------------------------------

template <class value_type>
s21::multiset<value_type>::multiset(const multiset& ms) {
  MultisetIterator it;
  it._node = ms._root;
  it._node = BST<value_type>::_MinimalNode(it._node);
  while (it._node != nullptr) {
    this->insert(*it);
    ++it;
  }
}

template <class value_type>
s21::multiset<value_type>::multiset(multiset&& ms) {
  if (this->_root != ms._root) {
    std::swap(this->_root, ms._root);
  }
}

template <class value_type>
void s21::multiset<value_type>::operator=(multiset&& ms) {
  if (this->_root != ms._root) {
    std::swap(this->_root, ms._root);
  }
}

// -----------------------------------------------------------------------------

// Iterator
// -----------------------------------------------------------------------------

template <class value_type>
typename s21::multiset<value_type>::iterator
s21::multiset<value_type>::begin() {
  MultisetIterator returnIterator;
  returnIterator._node = BST<value_type>::_MinimalNode(this->_root);
  return returnIterator;
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::end() {
  MultisetIterator returnIterator;
  if (this->_root != nullptr) {
    returnIterator._node = BST<value_type>::_MaximalNode(this->_root)->_right;
  } else {
    returnIterator._node = this->_root;
  }
  return returnIterator;
}

// -----------------------------------------------------------------------------

// Capacity
// -----------------------------------------------------------------------------

template <class value_type>
bool s21::multiset<value_type>::empty() {
  return this->_root == nullptr ? true : false;
}

template <class value_type>
typename s21::multiset<value_type>::size_type
s21::multiset<value_type>::size() {
  size_type currentSize = 0;
  for (iterator it = this->begin(); it != this->end(); ++it) {
    currentSize++;
  }
  return currentSize;
}

template <class value_type>
typename s21::multiset<value_type>::size_type
s21::multiset<value_type>::max_size() {
  return set<value_type>::max_size();
}

// -----------------------------------------------------------------------------

// Modifiers
// -----------------------------------------------------------------------------

template <class value_type>
void s21::multiset<value_type>::clear() {
  this->_DeleteAllTree(this->_root);
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::insert(
    const value_type& value) {
  BST_Node* tempNode = BST<value_type>::_FindNode(this->_root, value);
  MultisetIterator returnIterator;
  BST<value_type>::_InsertInTree(value);
  if (tempNode != nullptr) {
    returnIterator._node = BST<value_type>::_FindNode(tempNode, value);
  } else {
    returnIterator._node = BST<value_type>::_FindNode(this->_root, value);
  }
  return returnIterator;
}

template <class value_type>
void s21::multiset<value_type>::erase(iterator& pos) {
  if (pos._node != nullptr) {
    BST<value_type>::_DeleteNode(this->_root, pos._node->_key);
  }
}

template <class value_type>
void s21::multiset<value_type>::swap(multiset&& other) {
  if (this->_root != other._root) {
    std::swap(this->_root, other._root);
  }
}

template <class value_type>
void s21::multiset<value_type>::merge(multiset& other) {
  if (this->_root != other._root) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      this->insert(*it);
    }
    other.clear();
  }
}
// -----------------------------------------------------------------------------

// Lookup
// -----------------------------------------------------------------------------

template <class value_type>
typename s21::multiset<value_type>::size_type s21::multiset<value_type>::count(
    const value_type& key) {
  size_type counter = 0;
  if (this->contains(key)) {
    MultisetIterator iter = this->find(key);
    while (*iter == key) {
      ++counter;
      ++iter;
    }
  }
  return counter;
}

template <class value_type>
typename s21::multiset<value_type>::iterator s21::multiset<value_type>::find(
    const value_type& key) {
  MultisetIterator returnIterator;
  returnIterator._node = BST<value_type>::_FindNode(this->_root, key);
  if (returnIterator._node == nullptr) {
    returnIterator = this->end();
  }
  return returnIterator;
}

template <class value_type>
bool s21::multiset<value_type>::contains(const value_type& key) {
  return this->find(key) != this->end() ? true : false;
}

template <class value_type>
typename s21::multiset<value_type>::iterator
s21::multiset<value_type>::lower_bound(const value_type& key) {
  MultisetIterator iter;
  iter = this->find(key);
  if (iter == this->end()) {
    if (key < *this->begin()) {
      iter = this->begin();
    } else {
      iter._node = new typename BST<value_type>::Node;
      if (!this->empty()) {
        iter._node->_key = this->size();
      } else {
        iter._node->_key = (value_type)0;
      }
      iter._fake = true;
    }
  }
  return iter;
}

template <class value_type>
typename s21::multiset<value_type>::iterator
s21::multiset<value_type>::upper_bound(const value_type& key) {
  MultisetIterator iter = this->find(key);
  if (iter != this->end()) {
    while (*iter == key) {
      ++iter;
    }
    if (iter == this->end()) {
      iter._node = new typename BST<value_type>::Node;
      iter._node->_key = this->size();
      iter._fake = true;
    }
  } else {
    if (key < *this->begin()) {
      iter = this->begin();
    } else {
      iter._node = new typename BST<value_type>::Node;
      if (!this->empty()) {
        iter._node->_key = this->size();
      } else {
        iter._node->_key = (value_type)0;
      }
      iter._fake = true;
    }
  }
  return iter;
}

template <class value_type>
std::pair<typename s21::multiset<value_type>::iterator,
          typename s21::multiset<value_type>::iterator>
s21::multiset<value_type>::equal_range(const value_type& key) {
  return std::make_pair(this->lower_bound(key), this->upper_bound(key));
}

// -----------------------------------------------------------------------------

// Emplace
// -----------------------------------------------------------------------------

template <class value_type>
template <class... Args>
std::vector<std::pair<typename s21::multiset<value_type>::iterator, bool>>
s21::multiset<value_type>::emplace(Args&&... args) {
  std::vector<std::pair<iterator, bool>> resultVector;
  std::vector<value_type> itemVector = {args...};
  for (auto& item : itemVector) {
    auto pair = std::make_pair(this->insert(item), true);
    resultVector.push_back(pair);
  }
  return resultVector;
}

template <class value_type>
std::vector<std::pair<typename s21::multiset<value_type>::iterator, bool>>
s21::multiset<value_type>::emplace() {
  std::vector<std::pair<iterator, bool>> resultVector;
  resultVector.push_back(std::make_pair(this->end(), false));
  return resultVector;
}
// -----------------------------------------------------------------------------

#endif  // MY_MULTISET_H
