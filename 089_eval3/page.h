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
  vector<int> getChoices(void) {
    vector<int> num;
    for (unsigned long i = 0; i < choices.size(); i++) {
      num.push_back(choices[i].num);
    }
    return num;
  }
  int getNum(int cin) { return choices[cin - 1].num; }
  int pWL(void) { return ans; }
};

void pPrompt(void);
Page parsePage(ifstream & page);
Choice parseChoice(string line);
template<typename T>
bool find(vector<T> v, T & i);
void pStory(vector<Page> pages);
char * filepath(char * dire, int i);
