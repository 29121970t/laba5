#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*Allocate SIZE bytes of memory and exit programm on error*/
size_t malloc_s(size_t __size, void** ptr);

/*allocate NMEMB elements of SIZE bytes each, all initialized to 0 and exit programm on error*/
size_t calloc_s(size_t __nmemb, size_t __size, void** ptr);

/*Re-allocate the previously allocated block in PTR, making the new block SIZE bytes longs and exit programm on error*/
size_t realloc_s(void** __ptr, size_t __size);

int isDigit(char c);
int isValidIntChar(char c);
int isSpace(char c);
int isValidDoubleChar(char c);
int isValidDoubleStringChar(char c);
int isValidIntString(char c);
int isValidString(char* str, int (*validator)(char));
int isValidString_l(char* str, size_t length, int (*validator)(char));

size_t getLine(char** string, size_t* size, FILE* stream);
size_t readLine(char** string, size_t* size);
size_t readYNWithDialog(const char* str, int * res);
size_t readUDWithDialog(const char* str, int * res);

long parseLong(char* startPtr, char** endPtr);
size_t parseMultLong(long** array, char separator, char* inputString, size_t* count);
size_t readLong(long* ptr);
size_t readMultLong(long** array, char separator, size_t * count);
size_t readMultLongWithDialog(long** array, char separator, const char* massege, size_t* count);
size_t readLongWithDialog(long* ptr, char * messege);


double parseDouble(char* startPtr, char** endPtr);
size_t parseMultDouble(double** array, char separator, char* inputString, size_t * count);
size_t readMultDouble(double** array, char separator, size_t * count);
size_t readMultDoubleWithDialog(double** array, char separator, const char* massege, size_t * count);
size_t readDoubleWithDialog(double* ptr, char * messege);