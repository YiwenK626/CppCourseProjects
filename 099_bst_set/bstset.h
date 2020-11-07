#include <cstdio>
#include <cstdlib>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL){};
    Node(const K & key) : key(key), left(NULL), right(NULL){};
  };
  Node * root;

 public:
  BstSet() : root(NULL){};

  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }
  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  BstSet & operator=(const BstSet & rhs) {
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

  virtual void add(const K & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->key == key) {
        return;
      }
      else if ((*current)->key > key) {
        current = &((*current)->left);
      }
      else {
        current = &((*current)->right);
      }
    }
    *current = new Node(key);
  }
  virtual bool contains(const K & key) const {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return true;
      }
      else if (current->key > key) {
        current = (current->left);
      }
      else {
        current = (current->right);
      }
    }
    return false;
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

  virtual ~BstSet<K>() { destroy(root); }
};
