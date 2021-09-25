#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG 1

enum Errors {
	NOERRORS,      //0
	NOINPUTFILE,   //1
	NOOUTPUTFILE,  //2
	TOOMANYARGS    //3
};


/* ЕВГЕНИЙ ОНЕГИН */

struct MyString {
	char   *PtrOnStartOfString;
	size_t         LenOfString;
};

void  PrintGreetings       ();
void  ReadFromFile         (char **buffer_ptr, char* NameOfFile);
void  PrintFile            (MyString* Index,int NumberOfStrings);
void  PrintSeparator       (FILE *OutputFilePtr);
void  PrintBuffer          (char *buffer);
void  swap                 (MyString *Index, int i, int j);
void  Myqsort              (MyString *Index, int left, int right, int(*comparator)(const void *, const void *));
void  PrintGoodBye         ();
void  PrintBufferToFile    (FILE*  OutputFilePtr, char *buffer);
void  PrintToFile          (FILE*  OutputFilePtr, MyString *Index, int NumberOfStrings);
int   DecomposeToIndex     (MyString** Index_ptr, char **buffer_ptr);
int   GetNumberOfStrings   (char *buffer);
int   CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid);
int   CompareByLastLetters (const void* OneStringVoid, const void* AnotherStringVoid);
int   GetSizeOfFile        (FILE* FilePtr);
int   CloseOutputFile      (FILE*  OutputFilePtr);
int   ArgCheck             (int argc);
FILE *OpenOutputFile       (char* NameOfOutputFile);

