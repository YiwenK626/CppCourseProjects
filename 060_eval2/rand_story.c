#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCat(char * ptr) {
  char * key = malloc(strlen(ptr) + 1);
  char * target = malloc(sizeof(*target));
  strcpy(key, ptr);

  target = realloc(target, strlen(chooseWord(key, NULL)) + 1);
  strcpy(target, chooseWord(key, NULL));
  printf("%s", target);
  free(key);
  free(target);
}

void countDLT(char * line, char DLT, ssize_t len) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    if (line[0] == DLT) {
      count++;
    }
  }
  if (count % 2 != 0) {
    fprintf(stderr, "uneven number of underscores!\n");
    exit(EXIT_FAILURE);
  }
}
