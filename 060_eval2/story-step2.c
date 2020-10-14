#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "invalid number of inputs for step2\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;

  size_t n = 0;
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = n;
  cats->arr = malloc(n * sizeof(*cats->arr));
  char * temp = malloc(sizeof(*temp));

  while (len >= 0) {
    len = getline(&line, &sz, f);
    if (strchr(line, ':') == NULL) {
      fprintf(stderr, "invalid input format for step2\n");
      exit(EXIT_FAILURE);
    }

    temp = realloc(temp, strlen(line) + 1);
    strcpy(temp, line);

    // get category & word
    char * cat = strtok(temp, ":");
    char * word = strtok(NULL, ":");
    word[strlen(word) - 1] = '\0';

    // store into catarray
    if (n == 0) {
      n = firstEntry(n, cats, cat, word);
    }
    else {
      int sign = 0;
      for (int i = 0; i < n; i++) {
        category_t * T = &cats->arr[i];
        if (strcmp(T->name, cat) == 0) {  // entry of exsting category
          sign = 1;                       // change sign if cat name exists
          for (int j = 0; j < T->n_words; j++) {
            if (strcmp(T->words[j], word) == 0) {
              sign = 2;  //change sign and exit loop if word exits
            }
          }
          if (sign == 1) {
            T->n_words++;  // add to words array if not exist
                           //cpyWord(T->words, word, T->n_words);
            T->words = realloc(T->words, T->n_words * sizeof(*T->words));
            T->words[T->n_words - 1] = malloc(strlen(word) + 1);
            strcpy(T->words[T->n_words - 1], word);
          }
        }
      }
      if (sign == 0) {  // first entry of the category
        n = firstEntry(n, cats, cat, word);
      }
    }
  }
  // print catarray
  cats->n = n;
  printWords(cats);
  freeCatArr(cats, cats->n);
  free(temp);
  free(line);
  fclose(f);
  return 0;
}
