#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tomatrix(FILE * f) {
  int c;
  int i = 0;
  int j = 9;

  int matrix[11][11] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (c > 127) {
      fprintf(stderr, "unprintable char\n");
      return EXIT_FAILURE;
    }

    if (j < 0) {
      fprintf(stderr, "too much lines\n");
      return EXIT_FAILURE;
    }

    // printf("%c", c);
    matrix[i][j] = c;
    i++;

    if (i == 11) {
      j--;
      i = 0;
    }
  }
  // i j should exit loop as 0 and -1

  if (j >= 0) {
    fprintf(stderr, "too few lines\n");
    return EXIT_FAILURE;
  }

  for (int k = 0; k < 10; k++) {
    if (matrix[10][k] != '\n') {
      fprintf(stderr, "too much chars\n");
      return EXIT_FAILURE;
    }
  }

  for (int a = 0; a < 10; a++) {
    matrix[a][10] = '\n';
    for (int b = 0; b < 11; b++) {
      if (matrix[a][b] == '\n' && b < 10) {
        fprintf(stderr, "too few chars\n");
        return EXIT_FAILURE;
      }
      printf("%c", matrix[a][b]);
    }
  }
  // printf("\n");
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "enter file name");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  int exit = tomatrix(f);
  if (exit !=0) {
    fprintf(stderr, "EXIT with error\n");
    return EXIT_FAILURE;
    }

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
