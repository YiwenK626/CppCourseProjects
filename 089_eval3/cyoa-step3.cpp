#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>

#include "page.h"

using namespace std;

// step3: chekc reachability //

int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input argruments!\n";
    exit(EXIT_FAILURE);
  }

  vector<Page> pages = getPages(argv[1]);

  // check choice validity
  checkPages(pages);

  getRpages(pages);  // filter reachable pages and print out unreachable pages
}
