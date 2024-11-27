#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "lib/parseLib3.h"

void main() {
    printf("%d\n", errno);
    char* str = NULL;
    long* arr = NULL;
    size_t err = 0;
    size_t ammount = 0;
    size_t length = 0;
    //getLine(&str, &length, stdin);
    err = readMultLongWithDialog(&arr, ',', "HI THERE", &ammount);
    printf("%lu \n", err);
    // printf("%ld\n", parseLong(str, NULL));
    //   printf("%s\n\n", str);

    // printf("%ld\n", atol(str));

    
    for (int i = 0; i < ammount; i++) {
        printf("%ld, ", arr[i]);
    }


    puts("");
    free(str);
    free(arr);
    str = NULL;
    arr = NULL;
    
}