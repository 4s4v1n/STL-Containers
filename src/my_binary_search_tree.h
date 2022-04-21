#ifndef MY_BINARY_SEARCH_TREE_H
#define MY_BINARY_SEARCH_TREE_H

#include <iostream>

#define BST BinarySearchTree

namespace s21 {

template <class Key>
class BinarySearchTree {
 protected:
  typedef Key key_type;
  typedef key_type value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  struct Node {
    key_type _key;
    Node* _left;
    Node* _right;
    Node* _parent;
  };
  Node* _root;
  void _AddNode(Node*& tree, const key_type& key);
  Node*& _FindNode(Node*& tree, const key_type& key);
  void _DeleteNode(Node*& tree, const key_type& key);
  Node*& _MinimalNode(Node*& tree);
  Node*& _MaximalNode(Node*& tree);
  void _DeleteAllTree(Node*& tree);
  void _InsertInTree(const key_type& key);
  Node* _MinNodeWithOut(Node*& tree, Node*& changeNode);
  Node* _MaxNodeWithOut(Node*& tree, Node*& changeNode);
  BST();
  ~BST();
};

}  // namespace s21

template <class Key>
s21::BST<Key>::BST() {
  this->_root = nullptr;
}

template <class Key>
void s21::BST<Key>::_AddNode(Node*& tree, const key_type& key) {
  if (tree == nullptr) {
    tree = new Node;
    tree->_key = key;
    tree->_left = tree->_right = tree->_parent = nullptr;
  } else {
    if (key < tree->_key) {
      if (tree->_left != nullptr) {
        _AddNode(tree->_left, key);
      } else {
        tree->_left = new Node;
        tree->_left->_left = tree->_left->_right = nullptr;
        tree->_left->_parent = tree;
        tree->_left->_key = key;
      }
    } else {
      if (tree->_right != nullptr) {
        _AddNode(tree->_right, key);
      } else {
        tree->_right = new Node;
        tree->_right->_left = tree->_right->_right = nullptr;
        tree->_right->_parent = tree;
        tree->_right->_key = key;
      }
    }
  }
}

template <class Key>
void s21::BST<Key>::_InsertInTree(const key_type& key) {
  _AddNode(this->_root, key);
}

template <class Key>
typename s21::BST<Key>::Node*& s21::BST<Key>::_FindNode(Node*& tree,
                                                        const key_type& key) {
  return tree == nullptr || tree->_key == key ? tree
         : key < tree->_key                   ? _FindNode(tree->_left, key)
                                              : _FindNode(tree->_right, key);
}

template <class Key>
typename s21::BST<Key>::Node*& s21::BST<Key>::_MinimalNode(Node*& tree) {
  return tree->_left == nullptr ? tree : _MinimalNode(tree->_left);
}

template <class Key>
typename s21::BST<Key>::Node*& s21::BST<Key>::_MaximalNode(Node*& tree) {
  return tree->_right == nullptr ? tree : _MaximalNode(tree->_right);
}

template <class Key>
void s21::BST<Key>::_DeleteNode(Node*& tree, const key_type& key) {
  if (tree != nullptr) {
    if (tree->_key == key) {
      if (tree->_right == nullptr && tree->_left == nullptr) {
        delete tree;
        tree = nullptr;
      } else if (tree->_left != nullptr && tree->_right == nullptr) {
        tree->_left->_parent = tree->_parent;
        Node* tempNode = tree;
        tree = tree->_left;
        delete tempNode;
      } else if (tree->_right != nullptr && tree->_left == nullptr) {
        tree->_right->_parent = tree->_parent;
        Node* tempNode = tree;
        tree = tree->_right;
        delete tempNode;
      } else {
        tree->_key = _MinimalNode(tree->_right)->_key;
        _DeleteNode(tree->_right, tree->_key);
      }
    } else if (key < tree->_key) {
      _DeleteNode(tree->_left, key);
    } else {
      _DeleteNode(tree->_right, key);
    }
  }
}

template <class Key>
void s21::BST<Key>::_DeleteAllTree(Node*& tree) {
  if (tree != nullptr) {
    if (tree->_left != nullptr) {
      _DeleteAllTree(tree->_left);
    }
    if (tree->_right != nullptr) {
      _DeleteAllTree(tree->_right);
    }
    delete tree;
    tree = nullptr;
  }
}

template <class Key>
s21::BST<Key>::~BST() {
  _DeleteAllTree(this->_root);
}

template <class Key>
typename s21::BST<Key>::Node* s21::BST<Key>::_MinNodeWithOut(
    Node*& tree, Node*& changeNode) {
  return tree->_left == nullptr || tree->_left == changeNode
             ? tree
             : _MinNodeWithOut(tree->_left, changeNode);
}

template <class Key>
typename s21::BST<Key>::Node* s21::BST<Key>::_MaxNodeWithOut(
    Node*& tree, Node*& changeNode) {
  return tree->_right == nullptr || tree->_right == changeNode
             ? tree
             : _MaxNodeWithOut(tree->_right, changeNode);
}

#endif  // S21_BINARY_SEARCH_TREE_H
