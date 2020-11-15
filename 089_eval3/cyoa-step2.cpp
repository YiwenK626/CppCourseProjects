#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include "page.h"

using namespace std;

int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input argruments!\n";
    exit(EXIT_FAILURE);
  }

  // parse and store all pages into a vector
  // check format when parsing pages
  vector<Page> pages = getPages(argv[1]);

  // form a choice vector
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

  // each choice is valid: each element has a page
  validChoice<unsigned int>(allChoices, pages.size());

  // each page is referenced: each page is in choice vector
  for (unsigned int i = 2; i < pages.size() + 1; i++) {
    if (findV(allChoices, i) == 0) {
      cerr << "page " << i << " not referenced\n";
      exit(EXIT_FAILURE);
    }
  }
  // display the story
  pStory(pages);
}
