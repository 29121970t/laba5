#include <stdio.h>
#include <stdlib.h>

#include "lib/parseLib3.h"
#include "lib/randomLib.h"

void handleMallocError() {
    puts("MALLOC ERROR.");
    exit(1);
}

void printArray(double** inputArray, long size) {
    for (size_t i = 0; i < size; i++) {
        printf("| ");
        for (size_t j = 0; j < size; j++) {
            printf("%.1lf, ", inputArray[i][j]);
            if (inputArray[i][j] == 0) break;
        }
        printf("|\n");
    }
}

void fillByHand(double** inputArray, long size) {
    char tmpStr[100] = {0};
    for (long i = 0; i < size; i++) {
        int passFlag = 0;
        do {
            passFlag = 0;
            size_t count = 0;
            sprintf(tmpStr, "Please enter %ld-th row: %ld numbers > 0.", i + 1, size);
            if (readMultDoubleWithDialog(inputArray + i, ',', tmpStr, &count)) handleMallocError();

            for (size_t k = 0; k < count; k++) {
                if (inputArray[i][k] < 0) passFlag = 1;
            }

            if (count != size) {
                passFlag = 1;
                puts("Number count mismatch. Check your input and try again.");
                continue;
            }

            if (passFlag) puts("Got number <= 0. Check your input and try again.");
        } while (passFlag);
    }
}

void fillRandom(double** inputArray, long size) {
    long seed = 0;
    do {
        if (readLongWithDialog(&seed, "Please enter seed for random number generation (positive number < LONG_MAX)")) handleMallocError();
        if (seed <= 0) puts("Seed should be greater then 0. Please try again.");
    } while (seed <= 0);

    unsigned rand = MrandomUInt(seed);
    for (long i = 0; i < size; i++) {
        if ((inputArray[i] = calloc(size, sizeof(long))) == NULL) handleMallocError();

        for (int j = 0; j < size; j++) {
            rand = MrandomUInt(rand);
            inputArray[i][j] = map(0, 254803967, 2, 100, rand);
        }
    }

    puts("Random array:");
    printArray(inputArray, size);
}

void swap(double** a, double** b) {
    double* tmp = *a;
    *a = *b;
    *b = *a;
}

void main() {
    long size = 0;
    double** inputArray = NULL;
    char tmpStr[100] = {0};
    int byHandFlag = 0;
    int udFlag = 0;
    do {
        if (readLongWithDialog(&size, "Please enter size of the matrix (positive number < LONG_MAX)")) handleMallocError();
        if (size <= 0) puts("Row count should be greater then 0. Please try again.");
    } while (size <= 0);

    if ((inputArray = calloc(size, sizeof(double*))) == NULL) handleMallocError();

    readYNWithDialog("Fill by-hand? (Y/N):", &byHandFlag);
    readUDWithDialog("Shift Up or Down? (U/D)", &udFlag);

    byHandFlag ? fillByHand(inputArray, size) : fillRandom(inputArray, size);

    if (!udFlag) {
        double* tmpPtr = inputArray[0];
        for (long i = 0; i < size - 1; i++) {
            inputArray[i] = inputArray[i + 1];
        }
        inputArray[size - 1] = tmpPtr;
    } else {
        double* tmpPtr = inputArray[size - 1];
        for (long i = size - 1; i > 0; i--) {
            inputArray[i] = inputArray[i - 1];
        }
        inputArray[0] = tmpPtr;
    }

    puts("Result:");
    printArray(inputArray, size);

    for (size_t i = 0; i < size; i++) {
        free(inputArray[i]);
    }
    free(inputArray);
}