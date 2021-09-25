#include "NewOneg.h"

int main(int argc, char *argv[]) {

	int StatusArgCheck = ArgCheck(argc);
	assert(StatusArgCheck == 0);
	
	PrintGreetings();														//печатаем приветствие
	
	MyString *Index  = nullptr;												//пока не знаем размер массива структур
	char     *buffer = nullptr;												//будем читать туда файл

	
	char *INPUT_FILE = argv[1];
	char *OUTPUT_FILE = argv[2];

	ReadFromFile(&buffer, INPUT_FILE);										//записали весь файл в строку, это без \0
	assert(buffer);
	
	int NumberOfStrings = DecomposeToIndex(&Index, &buffer);				//разложит всё в индекс из буфера 

	qsort(Index, NumberOfStrings, sizeof(MyString), CompareByFirstLetters);	//сортровка первого вариантам

	FILE *OutputFilePtr = OpenOutputFile(OUTPUT_FILE);

	PrintSeparator(OutputFilePtr);											//печатает разделитель
	PrintToFile(OutputFilePtr, Index, NumberOfStrings);						//печатает файл(с помощью индекса
	PrintSeparator(OutputFilePtr);											//печатает разделитель
	
	Myqsort(Index, 0, NumberOfStrings - 1, CompareByLastLetters);			//сортировка второго варианта

	PrintToFile(OutputFilePtr, Index, NumberOfStrings);						//печатает файл
	PrintSeparator(OutputFilePtr);											//печатает разделитель
	PrintBufferToFile (OutputFilePtr, buffer);								//печатает исходный файл
	PrintSeparator(OutputFilePtr);											//печатает разделитель

	free(Index);
	free(buffer);

    int StatusOfCloseFile = CloseOutputFile(OutputFilePtr);
    assert(StatusOfCloseFile == 0);
	
	PrintGoodBye();
	
	return 0;
}
