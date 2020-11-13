#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>

#include "page.h"

using namespace std;

// one argv of dire
int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input argruments!\n";
    exit(EXIT_FAILURE);
  }

  vector<Page> pages = getPages(argv[1]);

  // check choice validity
  vector<unsigned int> allChoices;
  int win = 0;
  int lose = 0;
  for (vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
    vector<int> num = it->getChoices();
    allChoices.insert(allChoices.end(), num.begin(), num.end());
    if (it->pWL() == 1) {
      win++;
    }
    if (it->pWL() == -1) {
      lose++;
    }
  }
  if (!(win > 0 && lose > 0)) {  // at least one win and one lose
    cerr << "not enough WIN or LOSE pages\n";
    exit(EXIT_FAILURE);
  }
  set<unsigned int> reach;
  reach.insert(1);
  reach = addSet(pages, reach, 1);

  //iterate and print out those not in the set
  checkSet(pages.size(), reach);  // to check if members in pages are in reach
}

//a leap in page numbers ??

void checkSet(int size, set<unsigned int> container) {
  for (int i = 0; i < size; i++) {
    set<unsigned int>::iterator it;
    it = container.find(i + 1);
    if (it == container.end()) {
      cout << "Page " << i + 1 << " is not reachable\n";
    }
  }
}

set<unsigned int> addSet(vector<Page> pages,
                         set<unsigned int> container,
                         unsigned int startpoint) {
  if (startpoint <= pages.size()) {
    vector<int> num = pages[startpoint - 1].getChoices();

    for (vector<int>::iterator it = num.begin(); it != num.end(); ++it) {
      container.insert(*it);
      container = addSet(pages, container, *it);
    }
  }

  return container;
}
