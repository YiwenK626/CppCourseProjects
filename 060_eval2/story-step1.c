#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "incorrect number of arguments\n");
    exit(EXIT_FAILURE);
  }

  // initialization
  FILE * f = fopen(argv[1], "r");
  char * line = NULL;
  size_t size = 0;
  ssize_t len = 0;
  char * ptr;
  char * temp = malloc(sizeof(*temp));

  while (len >= 0) {
    len = getline(&line, &size, f);

    if (len != EOF) {
      // check if delimiters are paris
      countDLT(line, '_', len);

      int i = 0;
      temp = realloc(temp, strlen(line) + 1);
      strcpy(temp, line);
      ptr = strtok(temp, "_");

      // segment sentences into parts by "_"
      // directly printout text
      if (temp[0] != '_') {
        i++;
        printf("%s", ptr);
      }
      else {  // printout return value from chooseWord for blanks
        printCat(ptr);
        i += 2;
      }

      // read the next segment and repeat printing
      ptr = strtok(NULL, "_");

      // text and blanks show by turns
      // execute based on parity of i
      while (ptr != NULL) {
        if (i % 2 != 0) {
          printCat(ptr);
          i++;
        }
        else {
          printf("%s", ptr);
          i++;
        }
        ptr = strtok(NULL, "_");
      }
    }
  }
  free(line);
  free(temp);
  fclose(f);
}
