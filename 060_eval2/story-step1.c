#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "incorrect number of arguments for step1\n");
    exit(EXIT_FAILURE);
  }

  // initialization
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("NULL input");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t size = 0;
  ssize_t len = 0;
  char * ptr;
  char * temp = malloc(sizeof(*temp));

  while (len >= 0) {
    len = getline(&line, &size, f);

    if (len != EOF) {
      // check if delimiters are pairs
      countDLT(line, '_', len);

      temp = realloc(temp, strlen(line) + 1);
      strcpy(temp, line);
      ptr = strtok(temp, "_");  // segment sentences into parts by "_"

      // text and blanks show by turns
      // execute based on parity of int i
      int i = 0;
      if (temp[0] == '_') {
        i++;
      }

      while (ptr != NULL) {
        if (i % 2 != 0) {  // printout return value from chooseWord for blanks
          char * target = printCat(ptr, NULL, 0, NULL);
          free(target);
          i++;
        }
        else {  // directly printout text
          printf("%s", ptr);
          i++;
        }
        ptr = strtok(NULL, "_");  // read the next segment and repeat printing
      }
    }
  }
  free(line);
  free(temp);
  fclose(f);
  return 0;
}
