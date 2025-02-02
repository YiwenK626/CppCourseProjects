#include <cassert>
#include <cstdlib>
#include <iostream>
#include <list>
#include <set>
#include <vector>

using namespace std;

class Choice {
 public:
  int num;     // page number to go to
  string act;  // action if chosen
  Choice() : num(0), act(NULL){};
  Choice(int num, string act) : num(num), act(act){};
  Choice(const Choice & rhs) {
    num = rhs.num;
    act = rhs.act;
  }
  Choice & operator=(const Choice & rhs) {
    if (&rhs != this) {
      num = rhs.num;
      act = rhs.act;
    }
    return *this;
  }
  ~Choice(){};
};

class Page {
  int ans;
  vector<string> text;     // description
  vector<Choice> choices;  // choices

 public:
  Page() : ans(0), text(), choices(){};
  Page(int wl, vector<string> & desp, vector<Choice> & rhs) : ans(0), text(), choices() {
    if (wl != 0) {
      ans = wl;  // 1 for WIN and -1 for LOSE
    }
    else {
      for (unsigned long i = 0; i < rhs.size(); i++) {
        choices.push_back(rhs[i]);
      }
    }
    for (unsigned long j = 0; j < desp.size(); j++) {
      text.push_back(desp[j]);
    }
  };

  Page(const Page & rhs) : ans(0), text(), choices() {
    ans = rhs.ans;
    text = rhs.text;
    choices = rhs.choices;
  }
  Page & operator=(const Page & rhs) {
    if (&rhs != this) {
      ans = rhs.ans;
      text = rhs.text;
      choices = rhs.choices;
    }
    return *this;
  }

  ~Page(){};
  void pText(void) {  // print description by line
    for (unsigned long j = 0; j < text.size(); j++) {
      cout << text[j] << "\n";
    }
  }
  void pChoices(void) {  // print choices by serial number
    for (unsigned long i = 0; i < choices.size(); i++) {
      Choice c = choices[i];
      assert(c.num > 0);
      cout << " " << i + 1 << ". " << c.act << "\n";
    }
  }
  // store all availble choices of a page in a vector
  vector<unsigned int> getChoices(void) {
    vector<unsigned int> num;
    for (unsigned long i = 0; i < choices.size(); i++) {
      assert(choices[i].num > 0);
      num.push_back(choices[i].num);
    }
    return num;
  }
  // return page number by serial number cin
  int getNum(int cin) { return choices[cin - 1].num; }
  // return win/lose result if existed
  int pWL(void) { return ans; }
};

// print & parse
void pPrompt(void);
Page parsePage(ifstream & page);
Choice parseChoice(string line);
void pStory(vector<Page> pages);

// read inputs
char * filepath(char * dire, int i);
vector<Page> getPages(char * dire);
vector<Page> getRpages(vector<Page> pages);

// validity & reachability
set<unsigned int> addSet(vector<Page> pages,
                         set<unsigned int> container,
                         unsigned int startpoint);
vector<Page> checkSet(set<unsigned int> container, vector<Page> pages);
void checkPages(vector<Page> pages);
void validChoice(vector<unsigned int> choices, size_t MAX);
void refPage(vector<unsigned int> chocies, size_t MAX);

// get win route
int findWIN(vector<Page> rpages);
void pRoute(vector<Page> rpages, unsigned int endpoint);
vector<unsigned int> findRef(vector<Page> rpages, unsigned int endpoint);

// helpers
unsigned int findV(vector<unsigned int> v, unsigned int & i);
