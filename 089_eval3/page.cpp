#include "page.h"

#include <cassert>
#include <fstream>
#include <iostream>
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
    assert(line[0] == '#');
  }
  else if (line.compare("WIN") == 0) {
    wl = 1;
    getline(page, line);
    assert(line[0] == '#');
  }
  else {
    assert(isdigit(line[0]) != 0);
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
