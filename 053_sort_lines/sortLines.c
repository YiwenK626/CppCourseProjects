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
    printf("%s", data[n]);
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char * line_buf = NULL;
  size_t buf_size = 0;
  ssize_t line_size = 0;
  int i = 0;
  int size = 0;


  if (argc == 1) {
    char ** data = NULL; //malloc(size * sizeof(char *));
    while (line_size >= 0) {
      line_size = getline(&line_buf, &buf_size, stdin);
      size ++;
      data = realloc(data, size * sizeof(char *));
      data[i] = malloc(strlen(line_buf)+1);
      strcpy(data[i], line_buf); 
      i++;            
    }
    sortData(data, i-1);
    free(line_buf);
    for (int j = 0; j < i; j++){
      free(data[j]);
    }
    free(data);
  }
  else {
    int input = 1;
    char ** data;
    
    while (argv[input] != NULL) {
      FILE * f = fopen(argv[input], "r");
      if (!f) {
        fprintf(stderr, "Error opening file '%s'\n", argv[input]);
        exit(EXIT_FAILURE);
      }
      
      size = 0;
      i = 0;
      line_size = 0;
      line_buf = NULL;
      buf_size = 0;
      data = NULL; //= malloc(size * sizeof(char *));
      while (line_size >= 0) {
        line_size = getline(&line_buf, &buf_size, f);
        size ++;
        data = realloc(data, size * sizeof(char *));
        data[i] = malloc(strlen(line_buf)+1);
        strcpy(data[i], line_buf); 
        i++;           
      }
      sortData(data, i - 1);
      input++;
      free(line_buf);
      for (int j = 0; j < i; j++){
        free(data[j]);
      }      
      free(data);
      fclose(f);
      //fclose failure
    }
  }
  return EXIT_SUCCESS;
}
