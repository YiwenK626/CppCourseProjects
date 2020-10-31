#include <cstdlib>
#include <fstream>

#include "page.h"

using namespace std;
int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input!/n" << endl;
    exit(EXIT_FAILURE);
  }
  ifstream page;
  page.open(argv[1]);
  Page adv = parsePage(page);
  adv.pText();
  pPrompt();
  adv.pChoices();
  page.close();
}
