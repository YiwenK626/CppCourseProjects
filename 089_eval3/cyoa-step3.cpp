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

  getRpages(pages);  // filter reachable pages and print out unreachable pages
}

//a leap in page numbers ??
