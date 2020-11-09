#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  ifstream f;
  f.open(fname);
  uint64_t * dict = new uint64_t[257];
  for (size_t i = 0; i < 257; i++) {
    dict[i] = 0;
  }
  string line;
  getline(f, line);
  while (!f.eof()) {
    unsigned char ind;
    for (size_t i = 0; i < line.length(); i++) {
      ind = line[i];
      //if (ind == EOF) {
      //  dict[256] = 1;
      //}
      if (ind < 0) {
        cerr << line << ": " << i << "th char has ind as " << ind << endl;
        exit(EXIT_FAILURE);
      }
      //else {
      size_t m = ind;
      dict[m]++;
      //}
    }
    getline(f, line);
  }
  dict[256] = 1;
  f.close();
  return dict;
}
