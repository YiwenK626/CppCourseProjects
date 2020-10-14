#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "not enough inputs\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {  //without option -n
    getStory(0, argv);
  }
  else {  // with option -n
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "unknown option\n");
      exit(EXIT_FAILURE);
    }
    getStory(1, argv);
  }
}
void getStory(int option, char ** filename) {
  FILE * lib = fopen(filename[option + 1], "r");
  FILE * template = fopen(filename[option + 2], "r");
  if (lib == NULL || template == NULL) {
    perror("NULL input");
    exit(EXIT_FAILURE);
  }
  catarray_t * cats = malloc(sizeof(*cats));
  creatCats(lib, cats);
  parseTemp(template, cats, option);
  freeCatArr(cats, cats->n);
}
