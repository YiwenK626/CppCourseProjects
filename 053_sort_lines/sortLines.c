#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
  for (int n = 0; n < count; n++) {
    printf("%c", *(data[n]));
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char * line_buf = NULL;
  size_t buf_size = 0;
  ssize_t line_size = 0;
  int i = 0;
  char ** data = {0};
  if (argc == 1) {
    while (line_size >= 0) {
      line_size = getline(&line_buf, &buf_size, stdin);
      data[i] = line_buf;
      i++;
    }

    sortData(data, i + 1);
  }
  else {
    int i = 1;
    while (argv[i] != NULL) {
      FILE * f = fopen(argv[i], "r");
      if (!f) {
        fprintf(stderr, "Error opening file '%s'\n", argv[i]);
        exit(EXIT_FAILURE);
      }
      int count = 0;
      while (line_size >= 0) {
        count++;
        line_size = getline(&line_buf, &buf_size, f);
        sortData(&line_buf, buf_size);
      }
      fclose(f);
      //fclose failure
    }

    free(line_buf);
    line_buf = NULL;
    return EXIT_SUCCESS;
  }
}
