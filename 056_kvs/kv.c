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
  ssize_t len = getline(&line, &sz, f);
  if (len == EOF) {
    free(line);
    fclose(f);
    exit(EXIT_FAILURE);
  }

  int count = 0;
  kvarray_t * KVs = malloc(sizeof(*KVs));
  KVs->arr = malloc((count + 1) * sizeof(*KVs->arr));
  char temp[100] = "0";

  while (len >= 0) {
    len = getline(&line, &sz, f);
    strcpy(temp, line);

    KVs->arr = realloc(KVs->arr, (count + 1) * sizeof(*KVs->arr));

    //split them into pairs
    if (strchr(temp, '=') != NULL) {
      char * key;
      char * value;

      key = strtok(temp, "=");
      KVs->arr[count].key = (char *)malloc(strlen(key) + 1);
      //if (strchr(key, '\n') != NULL) {
      //  *strchr(key, '\n') = '\0';
      //}
      strcpy(KVs->arr[count].key, key);

      value = strtok(NULL, "");
      if (value != NULL) {
        *strchr(value, '\n') = '\0';
        KVs->arr[count].value = (char *)malloc(strlen(value) + 1);
        strcpy(KVs->arr[count].value, value);
      }
      else {
        KVs->arr[count].value = NULL;
      }
      //add the resulting pairs to an array with realloc
      count++;
    }
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
  // printf("%ld", pairs->size);
  for (int i = 0; i < pairs->size - 1; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].value);
  }
}
char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->size - 1; i++) {
    if (strcmp(pairs->arr[i].key, key) == 0) {
      return pairs->arr[i].value;
    }
  }
  return NULL;
}
