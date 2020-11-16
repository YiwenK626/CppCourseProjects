#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>

#include "page.h"

using namespace std;

// step 4: get winning route //

int main(int argc, char ** argv) {
  if (argc != 2) {
    cerr << "incorrect input argruments!\n";
    exit(EXIT_FAILURE);
  }

  // get reachable pages from 1-N pages
  vector<Page> pages = getPages(argv[1]);
  vector<Page> rpages = getRpages(pages);

  // find a WIN page
  int win = findWIN(rpages);
  // no WIN page
  if (win == -1) {
    cout << "There is no way to win\n";
    return EXIT_SUCCESS;
  }
  // has a WIN page
  else {
    pRoute(rpages, win);
    cout << "Page " << win << " WIN\n";
  }
}

int findWIN(vector<Page> rpages) {
  set<int> wins;
  for (unsigned i = 0; i < rpages.size(); i++) {
    if (rpages[i].pWL() == 1) {
      return i + 1;
    }
  }
  return -1;
}

void pRoute(vector<Page> rpages, unsigned int endpoint) {
  if (endpoint != 1) {
    vector<unsigned int> ans = findRef(rpages, endpoint);
    // print route to former page recursively
    pRoute(rpages, ans[0]);
    cout << "Page " << ans[0] << " Choice " << ans[1] << endl;
  }
}

// get the former page of endpoint AND the serial numer of endpoint
vector<unsigned int> findRef(vector<Page> rpages, unsigned int endpoint) {
  for (unsigned int i = 0; i < rpages.size(); i++) {
    vector<unsigned int> choices = rpages[i].getChoices();
    // get the position if endpoint appears in a page's choices
    unsigned int num = findV(choices, endpoint);
    if (num > 0) {
      vector<unsigned int> ans(2, 0);
      ans[0] = i + 1;
      ans[1] = num;
      return ans;
    }
  }

  // can't find a former page for reachable pages
  cerr << "unreachable becomes reachable\n";
  exit(EXIT_FAILURE);
}
