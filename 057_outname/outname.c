#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * suffix = ".counts";
  size_t n = strlen(inputName) + strlen(suffix) + 1;
  char * output = malloc(n);
  strcpy(output, inputName);
  strcat(output, suffix);
  return output;
}
