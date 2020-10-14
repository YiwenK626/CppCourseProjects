#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// printCat prints and returns the chosen word with cat name as the key
char * printCat(char * ptr, catarray_t * cats, int option, category_t * usedWords) {
  const char * trial = chooseWord(ptr, cats);
  if (trial == NULL) {
    fprintf(stderr, "invalid category names\n");
    exit(EXIT_FAILURE);
  }
  while (option == 1 && checkReuse(trial, usedWords) == 1) {
    trial =
        chooseWord(ptr, cats);  // rechoose the word if it has been used under option -n
  }
  char * target = malloc(sizeof(*target));
  target = realloc(target, strlen(trial) + 1);
  strcpy(target, trial);
  printf("%s", target);
  return target;
}

// countDLT counts number of delimiters to check if format is legal
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

// firstEntry enters new categories to catarrays and update its size
size_t firstEntry(size_t n, catarray_t * cats, char * cat, char * word) {
  n++;
  cats->arr = realloc(cats->arr, n * sizeof(*cats->arr));

  //name
  cats->arr[n - 1].name = malloc(strlen(cat) + 1);
  strcpy(cats->arr[n - 1].name, cat);
  //n_words
  cats->arr[n - 1].n_words = 1;
  //words
  cats->arr[n - 1].words = malloc(sizeof(*(cats->arr[n - 1].words)));
  cats->arr[n - 1].words[0] = malloc(strlen(word) + 1);
  strcpy(cats->arr[n - 1].words[0], word);

  return n;
}

// freeCatArr frees catarray
void freeCatArr(catarray_t * cats, size_t n) {
  for (int i = 0; i < n; i++) {
    freeCat(cats->arr[i], cats->arr[i].n_words);
  }
  free(cats->arr);
  free(cats);
}

//free Cat frees category
void freeCat(category_t arr, size_t n) {
  free(arr.name);
  for (int j = 0; j < n; j++) {
    free(arr.words[j]);
  }
  free(arr.words);
}

//storeCate keeps records of words used in usedWords
void storeCat(char * target, category_t * used) {
  used->n_words++;
  used->words = realloc(used->words, used->n_words * sizeof(*used->words));
  used->words[used->n_words - 1] = malloc(strlen(target) + 1);
  strcpy(used->words[used->n_words - 1], target);
}

// createCats creates a library for cat:word references
void creatCats(FILE * f, catarray_t * cats) {
  char * line = NULL;
  size_t size = 0;
  ssize_t len = 0;

  size_t n = 0;
  cats->n = n;
  cats->arr = malloc(n * sizeof(*cats->arr));
  char * temp = malloc(sizeof(*temp));

  while (len != EOF) {
    len = getline(&line, &size, f);
    if (strchr(line, ':') == NULL) {
      fprintf(stderr, "invalid input format for cats\n");
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
  cats->n = n;
  free(temp);
  free(line);
  fclose(f);
}

// parseTemp readst the word template and subtitutes blanks
void parseTemp(FILE * f, catarray_t * cats, int option) {
  // parse template
  char * line = NULL;
  size_t size = 0;
  ssize_t len = 0;
  char * ptr;
  char * temp = malloc(sizeof(*temp));

  category_t * usedWords = malloc(sizeof(*usedWords));
  usedWords->name = malloc(strlen("usedWords") + 1);
  strcpy(usedWords->name, "usedWords");
  usedWords->n_words = 0;
  usedWords->words = malloc(sizeof(*usedWords->words));

  while (len >= 0) {
    len = getline(&line, &size, f);

    if (len != EOF) {
      countDLT(line, '_', len);

      temp = realloc(temp, strlen(line) + 1);
      strcpy(temp, line);
      ptr = strtok(temp, "_");

      int i = 0;
      if (temp[0] == '_') {
        i++;
      }

      while (ptr != NULL) {
        // if text, print
        if (i % 2 == 0) {
          printf("%s", ptr);
          i++;
        }
        // if blanks, search
        else {
          // if cat, get word
          if (isdigit(*ptr) == 0) {
            char * target = printCat(ptr, cats, option, usedWords);
            storeCat(target, usedWords);
            free(target);
          }
          // if numbers, get record
          else {
            if (atoi(ptr) < 1) {
              fprintf(stderr, "fail to track back previous words with negative values\n");
              exit(EXIT_FAILURE);
            }
            else {
              int id = usedWords->n_words - atoi(ptr);
              if (id < 0) {
                fprintf(stderr, "integer blank index without previous words\n");
                exit(EXIT_FAILURE);
              }
              printf("%s", usedWords->words[id]);
              storeCat(usedWords->words[id], usedWords);
            }
          }
          i++;
        }
        ptr = strtok(NULL, "_");
      }
    }
  }
  free(temp);
  free(line);
  freeCat(*usedWords, usedWords->n_words);
  free(usedWords);
  fclose(f);
}

//checkReuse finds if the word has been used or not
int checkReuse(const char * target, category_t * usedWords) {
  for (int i = 0; i < usedWords->n_words; i++) {
    if (strcmp(target, usedWords->words[i]) == 0) {
      return 1;
    }
  }
  return 0;
}
