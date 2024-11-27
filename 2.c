#include <stdio.h>
#include <stdlib.h>

#include "lib/parseLib3.h"
#include "lib/randomLib.h"

void handleMallocError() {
    puts("MALLOC ERROR.");
    exit(1);
}

void printArray(long ** inputArray, long rowCount){
    for (size_t i = 0; i < rowCount; i++) {
        printf("| ");
        for (size_t j = 0; j < ULONG_MAX; j++) {
            printf("%ld, ", inputArray[i][j]);
            if (inputArray[i][j] == 0) break;
        }
        printf(" |\n");
    }
}

void removeMinInRow(long** inputArray, size_t rowCount) {
    for (size_t i = 1; i < rowCount; i += 2) {
        long* tpmPtr = NULL;
        size_t length = 0;
        size_t minIndex = 0;

        for (length = 0; length < ULONG_MAX; length++) {
            if (inputArray[i][length] == 0) break;
            if (inputArray[i][minIndex] > inputArray[i][length]) minIndex = length;
        }

        if ((tpmPtr = calloc(length, sizeof(long))) == NULL) handleMallocError();

        for (size_t j = 0, cursor = 0; j < length && cursor < length; j++, cursor++) {
            if (j == minIndex) cursor++;
            tpmPtr[j] = inputArray[i][cursor];
        }

        free(inputArray[i]);
        inputArray[i] = tpmPtr;
    }
}

void fillByHand(long** inputArray, long rowCount) {
    char tmpStr[100] = {0};
    for (long i = 0; i < rowCount; i++) {
        int passFlag = 0;
        do {
            passFlag = 0;
            size_t count = 0;
            sprintf(tmpStr, "Please enter %ld-th row. All numbers but last should be > 0. The last one should be 0.", i + 1);
            if (readMultLongWithDialog(inputArray + i, ',', tmpStr, &count)) handleMallocError();

            for (size_t k = 0; k < count - 1; k++) {
                if (inputArray[i][k] <= 0) passFlag = 1;
            }
            if (count < 2) {
                puts("Too few numbers (at least 2)");
                continue;
            }
            if (inputArray[i][count - 1] != 0) {
                puts("Last number is not zero");
                continue;
            }

            if (passFlag) puts("Got number <= 0.");
        } while (passFlag);
    }
}

void fillRandom(long** inputArray, long rowCount) {
    long seed = 0;
    do {
        if (readLongWithDialog(&seed, "Please enter seed for random number generation (positive number < LONG_MAX)")) handleMallocError();
        if (seed <= 0) puts("Seed should be greater then 0. Please try again.");
    } while (seed <= 0);

    unsigned rand = MrandomUInt(seed);
    for (long i = 0; i < rowCount; i++) {
        rand = MrandomUInt(rand);
        long length = map(0, 254803967, 2, 8, rand);

        if ((inputArray[i] = calloc(length, sizeof(long))) == NULL) handleMallocError();

        for (int j = 0; j < length - 1; j++) {
            rand = MrandomUInt(rand);
            inputArray[i][j] = map(0, 254803967, 2, 100, rand);
        }
        inputArray[i][length - 1] = 0;
    }

    puts("Random array:");
    printArray(inputArray, rowCount);
}

void main() {
    long rowCount = 0;
    long** inputArray = NULL;
    char tmpStr[100] = {0};
    int byHandFlag = 0;
    do {
        if (readLongWithDialog(&rowCount, "Please enter row count (positive number < LONG_MAX)")) handleMallocError();
        if (rowCount <= 0) puts("Row count should be greater then 0. Please try again.");
    } while (rowCount <= 0);

    if ((inputArray = calloc(rowCount, sizeof(long*))) == NULL) handleMallocError();

    readYNWithDialog("Fill by-hand? (Y/N):", &byHandFlag);

    byHandFlag ? fillByHand(inputArray, rowCount) : fillRandom(inputArray, rowCount);

    
    removeMinInRow(inputArray, rowCount);

    puts("Result:");
    printArray(inputArray, rowCount);


    for (size_t i = 0; i < rowCount; i++) {
        free(inputArray[i]);
    }
    free(inputArray);
}