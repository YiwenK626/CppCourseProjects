#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
const char * chooseWords(char * category, catarray_t * cats);

void printWords(catarray_t * cats);

void printCat(char * ptr);

void countDLT(char * line, char DLT, ssize_t len);

#endif
