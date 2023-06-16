#ifndef HW6_2_SORTALGORITHM_H
#define HW6_2_SORTALGORITHM_H

#include "parseFreeRewrite.h"

void quickSort(Book_t *database, int low, int high, bool (*compare)(void*, void*), size_t offset);
bool compareIntegers(void *firstInteger, void *secondNumber);
bool compareStrings(void *firstString, void *secondString);
bool compareDoubles(void *firstFloat, void *secondFloat);

#endif //HW6_2_SORTALGORITHM_H
