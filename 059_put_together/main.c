#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");

  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  int count = 0;
  char ** list = malloc(count * sizeof(*list));
  char temp[30] = "";

  while (len >= 0) {
    len = getline(&line, &sz, f);
    if (len != EOF) {
      strncpy(temp, line, strlen(line));
      temp[strlen(line) - 1] = '\0';
      char * value = lookupValue(kvPairs, temp);
      printf("%s, %s\n", temp, value);
      count++;

      list = realloc(list, count * sizeof(*list));
      if (value == NULL) {
        list[count - 1] = NULL;
      }
      else {
        list[count - 1] = malloc(strlen(value) + 1);
        strcpy(list[count - 1], value);
      }
    }
  }
  free(line);
  //free(temp);
  counts_t * c = createCounts();
  for (int i = 0; i < count; i++) {
    addCount(c, list[i]);
    free(list[i]);
  }
  free(list);
  fclose(f);
  return c;
}
int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  if (argc < 3) {
    printf("not enough input files\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
