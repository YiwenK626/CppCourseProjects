#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>

#include "node.h"
#include "readFreq.h"

using namespace std;
void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  ifstream f(inFile);
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  char c;
  map<unsigned, BitString>::const_iterator it;

  while (!f.get(c).eof()) {
    unsigned char y = c;
    it = theMap.find(y);
    if (it == theMap.end()) {
      printf("%u", y);
      cerr << "error in the Map!\n";
      exit(EXIT_FAILURE);
    }
    BitString b = (it->second);
    bfw.writeBitString(b);
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  assert(theMap.find(256) != theMap.end());
  bfw.writeBitString((theMap.find(256))->second);
  //bitfilewriter will close the output file in its destructor
  //but you probably need to close your input file.
  f.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //write your code here
  //implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * counts = readFrequencies(argv[1]);
  Node * tree = buildTree(counts);
  map<unsigned, BitString> theMap;
  BitString b;
  tree->buildMap(b, theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete[] counts;
  delete tree;

  return EXIT_SUCCESS;
}
