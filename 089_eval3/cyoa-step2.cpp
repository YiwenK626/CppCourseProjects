#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include "page.h"

using namespace std;

// step2: to display a game/directory/multi-pages //

int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input argruments!\n";
    exit(EXIT_FAILURE);
  }

  // parse and store all pages into a vector
  // check format when parsing pages
  vector<Page> pages = getPages(argv[1]);

  // check choice validity and page reference
  checkPages(pages);

  // display the story
  pStory(pages);
  return EXIT_SUCCESS;
}
