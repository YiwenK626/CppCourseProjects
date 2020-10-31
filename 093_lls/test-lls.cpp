#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>

#include "ll.h"

int main() {
  testList();
  return EXIT_SUCCESS;
}

void testList(void) {
  LinkedList<int> il1;
  LinkedList<int> il2;
  int ind = 1;

  if (il1.getSize() != 0) {  //getSize
    ind = 0;
  }
  for (int i = 0; i < 5; i++) {
    il2.addFront(i * i);  //addFront
    il2.addBack(-2 * i);  //addBack
  }
  if (il2.getSize() != 10) {
    ind = 0;
  }

  int a = il2.tail->data;
  int b = il2.head->data;

  if (a != -8 || b != 16) {
    ind = 0;
  }
  if (il2[0] != 16 || il2[9] != -8) {  //[]
    ind = 0;
  }
  il2.remove(0);           //remove
  if (il2.find(0) != 4) {  //find
    ind = 0;
  }

  il2.remove(0);
  if (il2.find(0) != -1) {
    ind = 0;
  }

  LinkedList<int> il3;
  il3.addFront(1);
  il3 = il2;
  for (int i = 0; i < il2.getSize(); i++) {
    if (il3[i] != il2[i]) {
      ind = 0;
      break;
    }
  }
  if (il3.tail->data != -8 || il3.head->data != 16) {
    ind = 0;
  }

  LinkedList<int> il4 = il2;
  for (int i = 0; i < il2.getSize(); i++) {
    if (il4[i] != il2[i]) {
      ind = 0;
      break;
    }
  }

  il4.remove(16);
  assert(il4.head->data == 9);
  assert(il4.head->next->data == 4);
  il4.remove(-8);
  assert(il4.tail->data == -6);
  assert(il4.tail->prev->data == -4);

  il3 = il1;
  if (ind == 0) {
    exit(EXIT_FAILURE);
  }
}
