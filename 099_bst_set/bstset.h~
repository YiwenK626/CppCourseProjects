#include <cstdio>
#include <cstdlib>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL){};
    Node(const K & key, const V & value) :
        key(key),
        value(value),
        left(NULL),
        right(NULL){};
  };
  Node * root;

 public:
  BstMap() : root(NULL){};

  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }
  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  BstMap & operator=(const BstMap & rhs) {
    if (&rhs != this) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
    current = NULL;
  }

  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->key == key) {
        (*current)->value = value;
        return;
      }
      else if ((*current)->key > key) {
        current = &((*current)->left);
      }
      else {
        current = &((*current)->right);
      }
    }
    *current = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return current->value;
      }
      else if (current->key > key) {
        current = (current->left);
      }
      else {
        current = (current->right);
      }
    }
    throw std::invalid_argument("key not found!\n");
  }
  virtual void remove(const K & key) {
    Node ** current = &root;
    Node * temp = NULL;
    while (*current != NULL) {
      if ((*current)->key == key) {
        //left null
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          *current = temp;
        }
        //right null
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          *current = temp;
        }
        //neither null
        else {
          // find the lowest larger node
          // right once then all left
          temp = (*current)->right;
          while (temp->left != NULL) {
            temp = temp->left;
          }
          (*current)->key = temp->key;
          (*current)->value = temp->value;
          ;
        }
      }
      else if ((*current)->key > key) {
        current = &((*current)->left);
      }
      else {
        current = &((*current)->right);
      }
    }
  }

  virtual ~BstMap<K, V>() { destroy(root); }
};
