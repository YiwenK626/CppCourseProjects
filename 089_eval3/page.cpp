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

template<typename T>
bool find(vector<T> v, T & i) {
  typename vector<T>::iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    if (*it == i) {
      return true;
    }
  }
  return false;
}

char * filepath(char * dire, int num) {
  stringstream fpath;
  fpath << dire << "/page" << num << ".txt";
  string fstring = fpath.str();

  char * f = new char[fstring.length() + 1];
  strcpy(f, fstring.c_str());

  return f;
}
