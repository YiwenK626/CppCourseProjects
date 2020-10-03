#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  //open the file
  FILE * f = fopen(fname, "r");
  //read the lines of the text
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;

  int count = 0;
  kvarray_t * KVs = malloc(sizeof(*KVs));
  KVs->arr = malloc((count + 1) * sizeof(*KVs->arr));
  char temp[100] = "0";

  while (len >= 0) {
    len = getline(&line, &sz, f);
    strcpy(temp, line);

    KVs->arr = realloc(KVs->arr, (count + 1) * sizeof(*KVs->arr));

    //split them into pairs
    char * key = strtok(temp, "=");
    if (key != NULL) {
      KVs->arr[count].key = (char *)malloc(strlen(key) + 1);
      strcpy(KVs->arr[count].key, key);
    }
    else {
      printf("no = in the inputs");
      exit(EXIT_FAILURE);
    }
    char * value = strtok(NULL, "");
    char * ptr = strchr(value, '\n');
    *ptr = '\0';
    KVs->arr[count].value = (char *)malloc(strlen(value) + 1);
    strcpy(KVs->arr[count].value, value);
    //add the resulting pairs to an array with realloc
    count++;
  }
  //close the file
  fclose(f);
  free(line);

  KVs->size = count;
  return KVs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < (pairs->size); i++) {
    free(pairs->arr[i].key);
    free(pairs->arr[i].value);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].value);
  }
}
char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->size; i++) {
    if (strcmp(pairs->arr[i].key, key) == 0) {
      return pairs->arr[i].value;
    }
  }
  return NULL;
}
