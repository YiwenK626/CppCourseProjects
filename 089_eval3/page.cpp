#include "page.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
Page parsePage(ifstream & page) {
  //parse win/lose
  string line;
  int wl = 0;
  getline(page, line);
  vector<Choice> rhs;
  if (line.compare("LOSE") == 0) {
    wl = -1;
    getline(page, line);
    if (line[0] != '#') {
      throw "invalid format: no # after LOSE ";
    }
  }
  else if (line.compare("WIN") == 0) {
    wl = 1;
    getline(page, line);
    if (line[0] != '#') {
      throw "invalid format: no # after WIN ";
    }
  }
  else {
    if (isdigit(line[0]) == 0) {
      throw "invalid format: neither choices nor results ";
    }
    rhs.push_back(parseChoice(line));
    getline(page, line);
    while (line[0] != '#') {
      rhs.push_back(parseChoice(line));
      getline(page, line);
    }
  }
  //after hashtag
  vector<string> desp;
  getline(page, line);
  while (!page.eof()) {
    desp.push_back(line);
    getline(page, line);
  }
  Page adv(wl, desp, rhs);
  return adv;
}
Choice parseChoice(string line) {
  size_t pos = line.find(':');
  int num = atoi(line.substr(0, pos).c_str());
  string act = line.substr(pos + 1);
  Choice cho(num, act);
  return cho;
}

void pPrompt(void) {
  cout << "\n";
  cout << "What would you like to do?\n";
  cout << "\n";
}

void pStory(vector<Page> pages) {
  Page * current = &pages[0];
  current->pText();
  while (current->pWL() == 0) {
    // enter choices
    pPrompt();
    current->pChoices();

    unsigned int i;
    cin >> i;
    while (i > (current->getChoices().size())) {
      cout << "That is not a valid choice, please try again\n";
      cin >> i;
    }
    current = &pages[current->getNum(i) - 1];
    current->pText();
  }
  cout << "\n";
  if (current->pWL() == 1) {
    cout << "Congratulations! You have won. Hooray!\n";
  }
  if (current->pWL() == -1) {
    cout << "Sorry, you have lost. Better luck next time!\n";
  }
  else {
    exit(EXIT_FAILURE);
  }
}

char * filepath(char * dire, int num) {
  stringstream fpath;
  fpath << dire << "/page" << num << ".txt";
  string fstring = fpath.str();

  char * f = new char[fstring.length() + 1];
  strcpy(f, fstring.c_str());

  return f;
}

vector<Page> getPages(char * dire) {
  int i = 1;

  ifstream page;
  page.open(filepath(dire, i));
  if (!page) {
    cerr << "fail to find page1.txt\n";
    exit(EXIT_FAILURE);
  }

  vector<Page> pages;
  while (page.is_open()) {
    try {
      pages.push_back(parsePage(page));
      //check format
    }
    catch (const char * msg) {
      cerr << msg << "in page" << i << ".txt\n";
      exit(EXIT_FAILURE);
    }
    page.close();
    i++;
    page.open(filepath(dire, i));
  }
  return pages;
}
// check which page is not in the reachable set and print them out
vector<Page> checkSet(set<unsigned int> container, vector<Page> pages) {
  vector<Page> rpages = pages;

  for (unsigned int i = 0; i < pages.size(); i++) {
    set<unsigned int>::iterator it;
    it = container.find(i + 1);
    if (it == container.end()) {
      cout << "Page " << i + 1 << " is not reachable\n";
      rpages.erase(rpages.begin() + i);
    }
  }
  return rpages;
}

// filter reachable pages by starting with choices in page 1
set<unsigned int> addSet(vector<Page> pages,
                         set<unsigned int> container,
                         unsigned int startpoint) {
  if (startpoint <= pages.size()) {
    vector<unsigned int> num = pages[startpoint - 1].getChoices();

    for (vector<unsigned int>::iterator it = num.begin(); it != num.end(); ++it) {
      container.insert(*it);
      container = addSet(pages, container, *it);
    }
  }

  return container;
}

//return reachable pages
vector<Page> getRpages(vector<Page> pages) {
  set<unsigned int> reach;
  reach.insert(1);
  reach = addSet(pages, reach, 1);

  return checkSet(reach, pages);
}

unsigned int findV(vector<unsigned int> v, unsigned int & i) {
  for (unsigned int j = 0; j < v.size(); j++) {
    if (v[j] == i) {
      return j + 1;
    }
  }
  return 0;
}
