#ifndef S21_SET_H
#define S21_SET_H

#include <vector>

#include "my_binary_search_tree.h"

#define BST_Node typename BST<value_type>::Node

namespace s21 {

template <class Key>
class set : protected BinarySearchTree<Key> {
 private:
  typedef Key key_type;
  typedef key_type value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

 public:
  class SetIterator : public BinarySearchTree<Key> {
   protected:
    BST_Node* _node;
    friend class set;

    BST_Node* _IncreaseIterator(BST_Node* tree, BST_Node* changeNode);
    BST_Node* _DecreaceIterator(BST_Node*& tree, BST_Node*& changeNode);

   public:
    SetIterator() { this->_node = nullptr; }
    ~SetIterator() { this->_node = nullptr; }
    void operator=(const SetIterator& other) {
      if (*this != other) {
        this->_node = other._node;
      }
    }
    value_type operator*() {
      return this->_node == nullptr ? (value_type)0 : this->_node->_key;
    }
    void operator++() {
      this->_node = _IncreaseIterator(this->_node, this->_node);
    }
    void operator--() {
      this->_node = _DecreaceIterator(this->_node, this->_node);
    }
    bool operator==(const SetIterator& other) {
      return this->_node == other._node;
    }
    bool operator!=(const SetIterator& other) {
      return this->_node != other._node;
    }

  };  // SetIterator
  typedef SetIterator iterator;
  typedef const SetIterator const_iterator;

  // Iterator
  iterator begin();
  iterator end();

  // Member functions
  set(){};
  explicit set(std::initializer_list<value_type> const& items) {
    for (auto& item : items) {
      this->insert(item);
    }
  }
  set(const set& s);
  set(set&& s);
  ~set(){};
  void operator=(set&& s);

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator& pos);
  void swap(set& other);
  void merge(set& other);

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Lookup
  iterator find(const Key& key);
  bool contains(const Key& key);

  // Emplace
  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args);
  std::vector<std::pair<iterator, bool>> emplace();

};  // set

}  // namespace s21

// Member functions
// -----------------------------------------------------------------------------
template <class value_type>
s21::set<value_type>::set(const set& s) {
  SetIterator it;
  it._node = s._root;
  it._node = BST<value_type>::_MinimalNode(it._node);
  while (it._node != nullptr) {
    this->insert(*it);
    ++it;
  }
}

template <class value_type>
s21::set<value_type>::set(set&& s) {
  if (this->_root != s._root) {
    std::swap(this->_root, s._root);
  }
}

template <class value_type>
void s21::set<value_type>::operator=(set&& s) {
  if (this->_root != s._root) {
    std::swap(this->_root, s._root);
  }
}
// -----------------------------------------------------------------------------

// Iterator
// -----------------------------------------------------------------------------
template <class value_type>
typename s21::set<value_type>::iterator s21::set<value_type>::begin() {
  SetIterator returnIterator;
  if (!this->empty()) {
    BST_Node* tempNode = BST<value_type>::_MinimalNode(this->_root);
    returnIterator._node = tempNode;
  } else {
    returnIterator._node = this->_root;
  }
  return returnIterator;
}

template <class value_type>
typename s21::set<value_type>::iterator s21::set<value_type>::end() {
  SetIterator returnIterator;
  if (!this->empty()) {
    BST_Node* tempNode = BST<value_type>::_MaximalNode(this->_root)->_right;
    returnIterator._node = tempNode;
  } else {
    returnIterator._node = this->_root;
  }
  return returnIterator;
}
// -----------------------------------------------------------------------------

template <class value_type>
typename s21::BST<value_type>::Node*
s21::set<value_type>::iterator::_IncreaseIterator(BST_Node* tree,
                                                  BST_Node* changeNode) {
  if (tree->_right != nullptr && tree->_right != changeNode) {
    return BinarySearchTree<value_type>::_MinNodeWithOut(tree->_right,
                                                         changeNode);
  }
  if (changeNode->_parent == tree) {
    return changeNode;
  }
  BST_Node* tempNode = tree->_parent;
  while (tempNode != changeNode && tempNode && tree == tempNode->_right) {
    tree = tempNode;
    tempNode = tempNode->_parent;
  }
  return tempNode;
}

template <class value_type>
typename s21::BST<value_type>::Node*
s21::set<value_type>::iterator::_DecreaceIterator(BST_Node*& tree,
                                                  BST_Node*& changeNode) {
  if (tree->_left != nullptr && tree->_left != changeNode) {
    return BST<value_type>::_MaxNodeWithOut(tree->_left, changeNode);
  }
  BST_Node* tempNode = tree->_parent;
  while (tempNode != changeNode && tree == tempNode->_left) {
    tree = tempNode;
    tempNode = tempNode->_parent;
    if (tempNode == nullptr) {
      return changeNode;
    }
  }
  return tempNode;
}

// Modifiers
// -----------------------------------------------------------------------------
template <class value_type>
void s21::set<value_type>::clear() {
  if (this->_root != nullptr) {
    BST<value_type>::_DeleteAllTree(this->_root);
  }
}

template <class value_type>
std::pair<typename s21::set<value_type>::iterator, bool>
s21::set<value_type>::insert(const value_type& value) {
  std::pair<iterator, bool> returnPair;
  BST_Node* tempNode = BST<value_type>::_FindNode(this->_root, value);
  if (tempNode == nullptr) {
    BST<value_type>::_InsertInTree(value);
    tempNode = BST<value_type>::_FindNode(this->_root, value);
    if (tempNode != nullptr) {
      returnPair.second = true;
      SetIterator tempIterator;
      tempIterator._node = tempNode;
      returnPair.first = tempIterator;
    } else {
      returnPair.second = false;
      returnPair.first = this->end();
    }
  } else {
    returnPair.first = this->end();
    returnPair.second = false;
  }
  return returnPair;
}

template <class value_type>
void s21::set<value_type>::erase(iterator& pos) {
  if (pos._node != nullptr) {
    BST<value_type>::_DeleteNode(this->_root, pos._node->_key);
  }
}

template <class value_type>
void s21::set<value_type>::swap(set& other) {
  if (this->_root != other._root) {
    std::swap(this->_root, other._root);
  }
}

template <class value_type>
void s21::set<value_type>::merge(set& other) {
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
typename s21::set<value_type>::iterator s21::set<value_type>::find(
    const value_type& key) {
  SetIterator returnIterator;
  returnIterator._node = BST<value_type>::_FindNode(this->_root, key);
  if (returnIterator._node == nullptr) {
    returnIterator = this->end();
  }
  return returnIterator;
}

template <class value_type>
bool s21::set<value_type>::contains(const value_type& key) {
  return this->find(key) != this->end() ? true : false;
}
// -----------------------------------------------------------------------------

// Capacity
// -----------------------------------------------------------------------------
template <class value_type>
bool s21::set<value_type>::empty() {
  return this->_root == nullptr ? true : false;
}

template <class value_type>
typename s21::set<value_type>::size_type s21::set<value_type>::size() {
  size_type currentSize = 0;
  for (iterator it = this->begin(); it != this->end(); ++it) {
    currentSize++;
  }
  return currentSize;
}

template <class value_type>
typename s21::set<value_type>::size_type s21::set<value_type>::max_size() {
  return size_type(-1) / sizeof(*this);
}
// -----------------------------------------------------------------------------

// Emplace
template <class value_type>
template <class... Args>
std::vector<std::pair<typename s21::set<value_type>::iterator, bool>>
s21::set<value_type>::emplace(Args&&... args) {
  std::vector<std::pair<iterator, bool>> resultVector;
  std::vector<value_type> itemVector = {args...};
  for (auto& items : itemVector) {
    auto insertResult = this->insert(items);
    resultVector.push_back(insertResult);
  }
  return resultVector;
}

template <class value_type>
std::vector<std::pair<typename s21::set<value_type>::iterator, bool>>
s21::set<value_type>::emplace() {
  std::vector<std::pair<iterator, bool>> resultVector;
  resultVector.push_back(std::make_pair(this->end(), false));
  return resultVector;
}

#endif  // MY_SET_H
