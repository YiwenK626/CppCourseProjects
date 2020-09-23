#include "pandemic.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //error: null input
  if (*line == '\n') {
    printf("Null input: blank line\n");
    exit(EXIT_FAILURE);
  }
  //error: untyped char
  int j = 0;
  while (line[j] != '\n') {
    if (line[j] > 127 || line[j] < 32) {
      printf("Illegal input: untypable char or no new line at the end\n");
      exit(EXIT_FAILURE);
    }
    j++;
  }

  //fetch country name
  int comma = ',';                    //identify delimiter
  char * ptr = strrchr(line, comma);  //find the last but also the only comma in line
  *ptr = '\0';                        //replace the delimter with a termination sign
  //error: multiple delimiter
  if (strchr(line, comma) != NULL) {  //if find another comma exit with failure
    printf("Illegal input: name contains ,\n");
    exit(EXIT_FAILURE);
  }
  country_t ans;
  strcpy(ans.name, line);

  //fetch population
  ptr++;
  //error: invalid number
  if (*ptr == '0') {
    ptr++;
    if (*ptr != '\n') {
      printf("Illegal input: population starts with zero or space\n");
      exit(EXIT_FAILURE);
    }
  }
  char arr[11] = {0};
  for (int i = 0; i < 11; i++) {
    if (*ptr != '\n') {  //read every digit into arr[]

      //error: invalid number
      if (i > 9) {
        printf(
            "Illegal input: too large country population\n");  //when the number is larger than 1000 billions
        exit(EXIT_FAILURE);
      }

      //error: invalid number
      if (isdigit(*ptr) == 0) {
        printf("Illegal input: population contains char\n");
        exit(EXIT_FAILURE);
      }
      arr[i] = *ptr;
      ptr++;
    }
    else {
      arr[i] = '\0';  //stop when read '\0'
      continue;
    }
  }
  int64_t pop = atoi(arr);  //switch char into int64_t
  ans.population = pop;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  for (int i = 0; i < n_days - 6;
       i++) {  //for each 7 days calculate sum and move to the next day as startpoint
    int sum = 0;
    for (int j = i; j < i + 7; j++) {
      //error: case data typo
      if (data[j] > 200000) {  // define daily case larger than 200,000 as potential error
        printf("data error: cases too large");
        exit(EXIT_FAILURE);
      }
      sum += data[j];
    }
    avg[i] = sum / 7.0;  //calculate 7-day moving average
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  int sum = 0;
  for (int i = 0; i < n_days;
       i++) {  //calculate cumulative cases among all population as days pass
    if (data[i] > 200000) {
      //error: case data typo
      printf("data error: cases too large");
      exit(EXIT_FAILURE);
    }
    sum += data[i];
    cum[i] = sum / (pop / 100000.0);  //calculate cases per 1000000 people
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned number_cases = 0;
  int ind_country = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] >
          number_cases) {  //update number_cases by scanning each iteam in the matrix
        number_cases = data[i][j];
        ind_country = i;  //once find a larger one, store its row (i.e. country) index
      }
    }
  }
  char * country_name = countries[ind_country].name;
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
