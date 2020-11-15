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
  vector<Page> rpages = getRpages(pages);

  // find a WIN page
  int win = findWIN(rpages);
  if (win == -1) {
    // no WIN page
    cout << "There is no way to win\n";
  }
  // has a WIN page
  else {
    pRoute(rpages, win);
    cout << "Page " << win << " WIN\n";
  }
}
