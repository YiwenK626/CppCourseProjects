#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tomatrix(FILE * f) {
  int c;
  int i = 0;
  int j = 9;
  int stop = 0;
  int matrix[11][11] = {0};
  while ((c = fgetc(f)) != EOF && stop == 0) {
    // printf("%c", c);
    matrix[i][j] = c;
    i++;
    if (i == 11) {
      j--;
      i = 0;
    }
    if (j < 0) {
      stop = 1;
    }
  }

  for (int a = 0; a < 10; a++) {
    matrix[a][10] = '\n';
    for (int b = 0; b < 11; b++) {
      printf("%c", matrix[a][b]);
    }
  }
  // printf("\n");
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "enter file name");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  tomatrix(f);
  if (f == NULL) {
    perror("could not open file");
    return EXIT_FAILURE;
  }

  if (fclose(f) != 0) {
    perror("failed to close file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
