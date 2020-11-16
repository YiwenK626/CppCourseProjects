#include "page.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

////////PART 1: PARSE AND DISPLAY PAGES////////

// reads pages into required categories: description, choices, results, etc.
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
    if (line[0] != '#') {  // invalid format
      throw "invalid format: no # after WIN ";
    }
  }
  // if no win/lose result now, read choices
  else {
    if (isdigit(line[0]) == 0) {  // invalid format
      throw "invalid format: neither choices nor results ";
    }
    rhs.push_back(parseChoice(line));
    getline(page, line);
    while (line[0] != '#') {  // # indicates where to stop
      rhs.push_back(parseChoice(line));
      getline(page, line);
    }
  }
  // read description after hashtag
  vector<string> desp;
  getline(page, line);
  while (!page.eof()) {
    desp.push_back(line);
    getline(page, line);
  }
  Page adv(wl, desp, rhs);
  return adv;
}

// read choices for parsePage()
// split choices into page numbers (by displaying order) and content
Choice parseChoice(string line) {
  size_t pos = line.find(':');
  int num = atoi(line.substr(0, pos).c_str());
  string act = line.substr(pos + 1);
  Choice cho(num, act);
  return cho;
}

// simply print prompt
void pPrompt(void) {
  cout << "\n";
  cout << "What would you like to do?\n";
  cout << "\n";
}

// display story by reading a vector of pages
void pStory(vector<Page> pages) {
  Page * current = &pages[0];
  // pText(), pChoice(): member functions of class Page
  current->pText();
  // current page has no win/lose
  while (current->pWL() == 0) {
    pPrompt();
    current->pChoices();

    // player enters non-digit -> exit games
    unsigned int i;
    cin >> i;
    if (i == 0) {  // cin is a char
      cerr << "You exit the game\n";
      break;
    }
    // player enters invalid choices -> re-enter
    while (i > (current->getChoices().size())) {
      cout << "That is not a valid choice, please try again\n";
      cin >> i;
    }
    current = &pages[current->getNum(i) - 1];
    current->pText();
  }
  cout << "\n";

  // current page has win/lose result
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
/////////////////////////////////////////////////

////////PART 2: OPEN DIRE AND STORE PAGES////////

// obtain the filepath of each page in dire
char * filepath(char * dire, int num) {
  stringstream fpath;
  fpath << dire << "/page" << num << ".txt";
  string fstring = fpath.str();

  char * f = new char[fstring.length() + 1];
  strcpy(f, fstring.c_str());

  return f;
}

// read pages from 1 to N until N+1 don't exist
vector<Page> getPages(char * dire) {
  int i = 1;
  // error: page1 does not exist
  ifstream page;
  page.open(filepath(dire, i));
  if (!page) {
    cerr << "fail to find page1.txt\n";
    exit(EXIT_FAILURE);
  }

  vector<Page> pages;
  while (page.is_open()) {
    try {
      // check format with parsePage()
      // add read results from parsePage() to vector pages
      pages.push_back(parsePage(page));
    }
    catch (const char * msg) {
      cerr << msg << "in page" << i << ".txt\n";
      exit(EXIT_FAILURE);
    }
    page.close();
    // open i+1 page until it does not exist
    i++;
    page.open(filepath(dire, i));
  }
  return pages;
}

////////////////////////////////////////

////////PART 3: CHECK VALIDITY//////////
void checkPages(vector<Page> pages) {
  // build a choice vector
  vector<unsigned int> allChoices;
  int win = 0;
  int lose = 0;
  for (vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
    // obtain all available choices of each page
    // add at the end of allChoices
    vector<unsigned int> num = it->getChoices();
    allChoices.insert(allChoices.end(), num.begin(), num.end());
    // calculate wins/loses
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

  // check: each choice is valid, i.e. each choice is in page 1-N
  validChoice(allChoices, pages.size());

  // check: each page is referenced, i.e. each page is in choices set
  refPage(allChoices, pages.size());
}

void validChoice(vector<unsigned int> choices, size_t MAX) {
  for (vector<unsigned int>::iterator it = choices.begin(); it != choices.end(); ++it) {
    if (*it > MAX) {
      cerr << "exist invalid references \n";
    }
  }
}

void refPage(vector<unsigned int> choices, size_t MAX) {
  for (unsigned int i = 2; i < MAX + 1; i++) {
    if (findV(choices, i) == 0) {
      cerr << "page " << i << " not referenced\n";
      exit(EXIT_FAILURE);
    }
  }
}

////////////////////////////////////////

////////PART 4: CHECK REACHABILITY//////

// get reachable pages
vector<Page> getRpages(vector<Page> pages) {
  set<unsigned int> reach;
  reach.insert(1);
  reach = addSet(pages, reach, 1);

  return checkSet(reach, pages);
}

// filter reachable pages numbers and add result to a set (container)
// start with page 1 (startpoint) and recurve
set<unsigned int> addSet(vector<Page> pages,
                         set<unsigned int> container,
                         unsigned int startpoint) {
  if (startpoint <= pages.size()) {
    // getChoices(): member function of class Page
    // returns a vector of available numbers for next page
    vector<unsigned int> num = pages[startpoint - 1].getChoices();

    for (vector<unsigned int>::iterator it = num.begin(); it != num.end(); ++it) {
      container.insert(*it);
      // recursively add choices of choices to set
      container = addSet(pages, container, *it);
    }
  }
  else {
    cerr << "pages out of scope!\n";  // error: pages not in 1-N
  }
  return container;
}

// print out pages not in reachable page number set
// erase unreachable pages and return only reachable pages
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

//////////////////////

////////HELPER////////

// return the first positon that an element occurs
unsigned int findV(vector<unsigned int> v, unsigned int & i) {
  for (unsigned int j = 0; j < v.size(); j++) {
    if (v[j] == i) {
      return j + 1;
    }
  }
  return 0;
}
