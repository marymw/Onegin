/* ЕВГЕНИЙ ОНЕГИН */

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG 1

#ifdef DEBUG
#define DEBUG_PRINTF(string) printf(string)
#define DEBUG_PRINTF_ONE_ARG(format,var) printf(format,var)
#else
#define DEBUG_PRINTF(string) printf("\n");
#endif

enum Errors {
	NOERRORS,      //0
	NOINPUTFILE,   //1
	NOOUTPUTFILE,  //2
	TOOMANYARGS    //3
};

struct MyString {
	char   *PtrOnStartOfString;
	size_t         LenOfString;
};

void  PrintGreetings       ();
void  ReadFromFile         (char **buffer_ptr, char* NameOfFile);
void  PrintFile            (MyString* Index, const int NumberOfStrings);
void  PrintSeparator       (FILE *OutputFilePtr);
void  PrintBuffer          (const char *buffer);
void  swap                 (MyString *Index, const int i, const int j);
void  Myqsort              (MyString *Index, int left, int right, int(*comparator)(const void *, const void *));
void  PrintGoodBye         ();
void  PrintBufferToFile    (FILE*  OutputFilePtr, const char *buffer);
void  PrintToFile          (FILE*  OutputFilePtr, MyString *Index, const int NumberOfStrings);
int   DecomposeToIndex     (MyString** Index_ptr, char **buffer_ptr);
int   GetNumberOfStrings   (const char *buffer);
int   CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid);
int   CompareByLastLetters (const void* OneStringVoid, const void* AnotherStringVoid);
int   GetSizeOfFile        (FILE* FilePtr);
int   CloseOutputFile      (FILE*  OutputFilePtr);
int   ArgCheck             (int argc);
FILE *OpenOutputFile       (char* NameOfOutputFile);

