#include <iostream>

#include "node.h"

using namespace std;
Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  // create a priority queue
  priority_queue_t pq;
  // read input
  // add new nodes to queue
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() != 1) {
    Node * l = pq.top();
    pq.pop();
    Node * r = pq.top();
    pq.pop();
    pq.push(new Node(l, r));
  }
  return pq.top();
}
