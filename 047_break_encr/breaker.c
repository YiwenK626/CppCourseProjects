#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int maxind(int * array, size_t n) {
  int c = array[0];
  int ind = 0;
  for (int i = 1; i < n; i++) {
    if (c < array[i]) {
      c = array[i];
      ind = i;
    }
  }
  return ind;
}

int freq(FILE * f) {
  int c;
  int i = 0;
  int array[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      int num = c - 'a';
      array[num]++;
    }
    i++;
  }
  int key;
  if (i == 0) {
    key = 0;
  }
  else {
    if (maxind(array, 26) < 'e') {
      key = 26 + maxind(array, 26) + 'a' - 'e';
    }
    else {
      key = maxind(array, 26) + 'a' - 'e';
    }
  }
  return key;
}

  void unencrypt(FILE * f, int key) {
    int c;
    while ((c = fgetc(f)) != EOF) {
      if (isalpha(c)) {
        printf("used to be %c\n", c);
        c -= key;
      }
      printf("should be %c\n", c);
    }
  }

  int main(int argc, char ** argv) {
    if (argc != 2) {
      fprintf(stderr, "Usage: input file name\n");
      return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("Could not open the file");
      return EXIT_FAILURE;
    }
    int key = freq(f);
    //unencrypted with key
    //unencrypt(f, key);

    if (fclose(f) != 0) {
      perror("Failed to close the input file");
      return EXIT_FAILURE;
    }
    printf("%d\n", key);
    return EXIT_SUCCESS;
  }
