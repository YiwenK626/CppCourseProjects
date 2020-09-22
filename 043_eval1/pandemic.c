#include "pandemic.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;
  //null input
  if (line == NULL) {
    ans.name[0] = '\0';
    ans.population = 0;
    printf("null input");
    return ans;
  }
  //untyped char
  int len = sizeof(line);
  for (int j = 0; j < len; j++) {
    if (line[j] > 255) {
      ans.name[0] = '\0';
      ans.name[0] = 0;
      printf("untypable char");
      return ans;
    }
  }
  //more or less inputs

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
  //unmatched country more or less
  //null add input

  for (int i = 0; i < n_days - 6; i++) {
    int sum = 0;
    for (int j = i; j < i + 7; j++) {
      sum += data[j];
    }
    avg[i] = sum / 7.0;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //unmatched coutry more or less
  //null add input
  int sum = 0;
  for (int i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = sum / (pop / 100000.0);
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned number_cases = 0;
  int ind_country = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > number_cases) {
        number_cases = data[i][j];
        ind_country = i;
      }
    }
  }
  char * country_name = countries[ind_country];
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
