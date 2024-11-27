#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/parseLib3.h"

void handleMallocError(){
    puts("MALLOC ERROR.");
    exit(1);
}

size_t removeNegative(double* inputArray, size_t size, double** result) {
    double* resultArray = NULL;
    if((resultArray = calloc(size, sizeof(double))) == NULL) handleMallocError();

    size_t cursor = 0;
    for (size_t i = 0; i < size; i++) {
        if (inputArray[i] >= 0) {
            resultArray[cursor] = inputArray[i];
            cursor++;
        }
    }
    if (cursor != 0 && (*result = realloc(resultArray, sizeof(double) * (cursor))) == NULL) handleMallocError(); 
    return cursor;
}

void main() {
    double* inputArray = NULL;
    double* resultArray = NULL;
    size_t tmpError = 0;
    size_t size = 0;

    tmpError = readMultDoubleWithDialog(&inputArray, ',', "Please enter members of array separated by commas.(1, 1.2, 3, ...) Use dot to separate fractional part.", &size);
    if (tmpError) handleMallocError();
    size_t newSize = removeNegative(inputArray, size, &resultArray);

    if (newSize == 0){
         puts("Result array is empty.");
         return;
    }

    puts("Result array:");
    for (size_t i = 0; i < newSize; i++) {
        printf("%lf, ", resultArray[i]);
    }
    putchar('\n');

    free(inputArray);
    free(resultArray);
}