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
    if (current == NULL) {
      return NULL;
    }
    if (data == current->data) {
      Node * ans = current->next;
      if (ans != NULL) {
        ans->prev = current->prev;
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
    Node ** list = new Node *[rhs.getSize()];
    head = list[0];
    tail = list[rhs.getSize()];

    for (int i = 0; i < rhs.getSize(); i++) {
      list[i]->data = rhs[i];
      if (i == rhs.getSize() - 1) {
        list[i]->next = NULL;
      }
      else {
        list[i]->next = list[i + 1];
      }
      if (i == 0) {
        list[i]->prev = NULL;
      }
      else {
        list[i]->prev = list[i - 1];
      }
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    Node ** list = new Node *[rhs.getSize()];
    LinkedList * ans = new LinkedList;
    ans->head = list[0];
    ans->tail = list[rhs.getSize()];

    for (int i = 0; i < rhs.getSize(); i++) {
      list[i]->data = rhs[i];
      if (i == rhs.getSize() - 1) {
        list[i]->next = NULL;
      }
      else {
        list[i]->next = list[i + 1];
      }
      if (i == 0) {
        list[i]->prev = NULL;
      }
      else {
        list[i]->prev = list[i - 1];
      }
    }
    return *ans;
  }
  ~LinkedList() {
    while (head != NULL) {
      delete head;
      head = head->next;
    }
    delete tail;
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
    head = rmN(item, head);
    if (head->next == NULL) {
      return 0;
    }
    else {
      return 1;
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
    int i = 0;
    while (temp->next != NULL) {
      temp = temp->next;
      i++;
    }

    return i;
  }
  friend void testList(void);
};
#endif
