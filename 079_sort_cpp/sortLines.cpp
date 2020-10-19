#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printVector(std::vector<std::string> v) {
  std::vector<std::string>::iterator it = v.begin();
  while (it != v.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string line;
    std::vector<std::string> strV;
    std::getline(std::cin, line);

    while (!std::cin.eof()) {
      strV.push_back(line);
      std::getline(std::cin, line);
    }
    std::sort(strV.begin(), strV.end());
    printVector(strV);
  }

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::ifstream fname;
      fname.open(argv[i]);
      if (!fname) {
        std::cerr << "fail to open " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }

      std::string line;
      std::vector<std::string> strV;
      std::getline(fname, line);
      if (fname.eof()) {
        std::cerr << "blank input file " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }

      while (!fname.eof()) {
        strV.push_back(line);
        std::getline(fname, line);
      }
      std::sort(strV.begin(), strV.end());
      printVector(strV);
      fname.close();
    }
  }

  return EXIT_SUCCESS;
}
