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

void pRoute(vector<Page> rpages, unsigned int endpoint) {
  if (endpoint != 1) {
    vector<unsigned int> ans = findRef(rpages, endpoint);
    pRoute(rpages, ans[0]);

    cout << "Page " << ans[0] << " Choice " << ans[1] << endl;
  }
}

vector<unsigned int> findRef(vector<Page> rpages, unsigned int endpoint) {
  for (unsigned int i = 0; i < rpages.size(); i++) {
    vector<unsigned int> choices = rpages[i].getChoices();
    unsigned int num = findV(choices, endpoint);
    if (num > 0) {
      vector<unsigned int> ans(2, 0);
      ans[0] = i + 1;
      ans[1] = num;
      return ans;
    }
  }

  cerr << "unreachable becomes reachable\n";
  exit(EXIT_FAILURE);
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
