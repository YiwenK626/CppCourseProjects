#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
class Choice {
 public:
  int num;
  string act;
  Choice() : num(0), act(NULL){};
  Choice(int num, string act) : num(num), act(act){};
};

class Page {
  int ans;
  vector<string> text;
  vector<Choice> choices;

 public:
  Page() : ans(0), text(), choices(){};
  Page(int wl, vector<string> & desp, vector<Choice> & rhs) : ans(0), text(), choices() {
    if (wl != 0) {
      ans = wl;
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
  ~Page(){};
  void pText(void) {
    for (unsigned long j = 0; j < text.size(); j++) {
      cout << text[j] << "\n";
    }
  }
  void pChoices(void) {
    for (unsigned long i = 0; i < choices.size(); i++) {
      cout << " " << i + 1 << ". " << choices[i].act << "\n";
    }
  }
  int pWL(void) { return ans; }
};

void pPrompt(void);
Page parsePage(ifstream & page);
Choice parseChoice(string line);
