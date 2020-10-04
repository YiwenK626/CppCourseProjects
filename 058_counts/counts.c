#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * arr = malloc(sizeof(*arr));
  arr->array = malloc(sizeof(*arr->array));
  arr->size = 0;
  arr->un_size = 0;
  return arr;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->un_size++;
  }
  else {
    c->size++;
    int sign = 0;
    c->array = realloc(c->array, c->size * sizeof(*c->array));
    //c->array[c->size - 1].string = malloc(sizeof(char));
    c->array[c->size - 1].count = 0;
    for (int i = 0; i < c->size - 1; i++) {
      if (strcmp(c->array[i].string, name) == 0) {
        c->array[i].count++;
        sign = 1;
        c->size--;
      }
    }
    if (sign == 0) {
      c->array[c->size - 1].string = malloc(strlen(name) + 1);
      strcpy(c->array[c->size - 1].string, name);
      c->array[c->size - 1].count++;
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c->size > 0) {
    for (int i = 0; i < c->size; i++) {
      fprintf(outFile, "%s: %d\n", c->array[i].string, c->array[i].count);
    }
  }
  if (c->un_size != 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->un_size);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  if (c->size > 0) {
    for (int i = 0; i < c->size; i++) {
      free(c->array[i].string);
    }
  }
  free(c->array);
  free(c);
}
