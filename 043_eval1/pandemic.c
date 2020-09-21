#include "pandemic.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  if (line == NULL) {
    ans.name[0] = '\0';
    ans.population = 0;
    printf("null input");
    return ans;
  }

  int len = sizeof(line);
  for (int j = 0; j < len; j++) {
    if (line[j] > 255) {
      ans.name[0] = '\0';
      ans.name[0] = 0;
      printf("untypable char");
      return ans;
    }
  }

  int coma = ',';
  char * ptr = strchr(line, coma);
  *ptr = '\0';
  ptr++;
  char arr[15] = {0};
  for (int i = 0; i < 15; i++) {
    if (*ptr != '\n') {
      arr[i] = *ptr;
      ptr++;
    }
    else {
      arr[i] = '\0';
      continue;
    }
  }
  int64_t pop = atoi(arr);
  strcpy(ans.name, line);
  ans.population = pop;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
