#include <cstdlib>
#include <fstream>

#include "page.h"

using namespace std;

// step1: to display one page //

int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input!/n" << endl;
    exit(EXIT_FAILURE);
  }
  ifstream page;
  page.open(argv[1]);
  Page adv = parsePage(page);
  adv.pText();  // class member function: print description
  // if page has no win/lose
  if (adv.pWL() == 0) {
    pPrompt();
    adv.pChoices();  // class memeber function: print choices
  }
  else {
    cout << "\n";
    if (adv.pWL() == 1) {  // win
      cout << "Congratulations! You have won. Hooray!\n";
    }
    if (adv.pWL() == -1) {  // lose
      cout << "Sorry, you have lost. Better luck next time!\n";
    }
    else {
      exit(EXIT_FAILURE);
    }
    page.close();
  }
}
