#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#define DEBAG 1
#define DEBUG 1


/* ЕВГЕНИЙ ОНЕГИН */

struct MyString {
	char *PtrOnStartOfString;
	size_t   LenOfString;
};//надо инициализировать??

void PrintGreetings       ();
int  ReadFromFile         (char **buffer_ptr, char* NameOfFile);
int  DecomposeToIndex     (MyString** Index_ptr, char **buffer_ptr);
int  GetNumberOfStrings   (char *buffer);
void PrintFile            (MyString* Index,int NumberOfStrings);
void PrintSeparator       ();
void PrintBuffer          (char *buffer);
int  CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid);
int  CompareByLastLetters (const void* OneStringVoid, const void* AnotherStringVoid);
void swap                 (MyString *Index, int i, int j);
void Myqsort              (MyString *Index, int left, int right, int(*comparator)(const void *, const void *));
int  GetSizeOfFile        (FILE* FilePtr);
void FreeMemory           (MyString ** Index_ptr, char **buffer_ptr);
int  DeleteEmptyStrings   (char *buffer, int NumberOfSymbols);

//int DeleteEmptyStrings(char *buffer, int NumberOfSymbols);
