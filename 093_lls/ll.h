#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
void testList(void);
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(const T & item, Node * next, Node * prev) : data(item), next(next), prev(prev){};
  };
  Node * rmN(const T & data, Node * current) {
    if (current == NULL) {  // when there is no sublist
      return NULL;
    }
    if (data == current->data) {  // when head is key
      Node * ans = current->next;
      if (ans != NULL) {
        ans->prev = current->prev;
      }
      else {
        tail = current->prev;
      }

      delete current;
      return ans;
    }
    current->next = rmN(data, current->next);
    return current;
  }

  Node * head;
  Node * tail;
  // int size;

 public:
  LinkedList() : head(NULL), tail(NULL){};
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
    Node * temp = rhs.tail;
    while (temp != NULL) {
      this->addFront(temp->data);
      temp = temp->prev;
    }
  }
  LinkedList<T> & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      Node * current = rhs.tail;
      while (current != NULL) {
        this->addFront(current->data);
        current = current->prev;
      }
    }
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
  };
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
  };
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
  }
  bool remove(const T & item) {
    LinkedList temp = *this;
    head = rmN(item, head);
    if (temp.getSize() == getSize()) {
      return false;
    }
    else {
      return true;
    }
  }
  T & operator[](int index) {
    int t = 0;
    Node * temp = head;
    while (t < index) {
      temp = temp->next;
      assert(temp != NULL);
      t++;
    }

    return temp->data;
  }
  const T & operator[](int index) const {
    if (index < 0 || index >= getSize()) {
      exit(EXIT_FAILURE);
    }

    int t = 0;
    Node * temp = head;
    while (t < index) {
      temp = temp->next;
      assert(temp != NULL);
      t++;
    }
    return temp->data;
  }
  int find(const T & item) {
    Node * temp = head;
    int i = 0;
    if (temp == NULL) {
      return -1;
    }
    while (temp->data != item) {
      temp = temp->next;
      if (temp == NULL) {
        return -1;
      }
      i++;
    }

    return i;
  }
  int getSize() const {
    if (head == NULL) {
      return 0;
    }
    Node * temp = head;
    int i = 1;
    while (temp->next != NULL) {
      temp = temp->next;
      i++;
    }

    return i;
  }
  friend void testList(void);
};
#endif
