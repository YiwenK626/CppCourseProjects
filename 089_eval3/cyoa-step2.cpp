#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "page.h"

using namespace std;

// one argv of dire
int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input argruments!\n";
    exit(EXIT_FAILURE);
  }

  int i = 1;

  ifstream page;
  page.open(filepath(argv[1], i));  //throw error

  vector<Page> pages;
  while (page.is_open()) {
    pages.push_back(parsePage(page));
    //check format
    page.close();
    i++;
    page.open(filepath(argv[1], i));
  }
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
  assert(win > 0 && lose > 0);  // at least one win and one lose

  // each choice is valid: each element has a page
  for (vector<unsigned int>::iterator it = allChoices.begin(); it != allChoices.end();
       ++it) {
    if (*it > pages.size()) {
      cerr << "exist invalid references \n";
    }
  }

  // each page is references: each page has an vector element
  for (unsigned int i = 2; i < pages.size() + 1; i++) {
    if (!find<unsigned int>(allChoices, i)) {
      cerr << "page " << i << " not references\n";
      exit(EXIT_FAILURE);
    }
  }
  // display the story
  pStory(pages);
}

template<typename T>
bool find(vector<T> v, T & i) {
  typename vector<T>::iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    if (*it == i) {
      return true;
    }
  }
  return false;
}
