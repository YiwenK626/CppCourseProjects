#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"

const char * chooseWords(char * category, catarray_t * cats);

void printWords(catarray_t * cats);

char * printCat(char * ptr, catarray_t * cats, int option, category_t * usedWords);

void countDLT(char * line, char DLT, ssize_t len);

size_t firstEntry(size_t n, catarray_t * cats, char * cat, char * word);

void parseTemp(FILE * f, catarray_t * cats, int option);

void getStory(int option, char ** filename);

void freeCatArr(catarray_t * cats, size_t n);

void freeCat(category_t cats, size_t n);

void creatCats(FILE * f, catarray_t * cats);

int checkReuse(const char * target, category_t * usedWords);

void storeCat(char * target, category_t * used);
#endif
