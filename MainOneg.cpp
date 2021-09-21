#include "HeadOneg.h"
int main(int argc, char *argv[]) {

	PrintGreetings();//печатаем приветствие
	
	MyString *Index  = nullptr;//пока не знаем размер массива структур
	char     *buffer = nullptr;//будем читать туда файл

	#ifdef DEBAG
		printf("%s\n", argv[1]);
		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	#endif

	int NumberOfSymbols = ReadFromFile(&buffer, argv[1]);//записали весь файл в строку, это без \0

	//int NewNumberOfSymbols = DeleteEmptyStrings(buffer, NumberOfSymbols + 1);

	#ifdef DEBAG
		//printf("Значение NewNumberOfSymbols равно = %d\n", NewNumberOfSymbols);
		if (buffer == nullptr)
			printf("buffer в функции main после ReadFromFile содержит нулевой указатель\n");
		if (buffer != nullptr) 
			printf("buffer в функции main после ReadFromFile содержит ненулевой указатель\n");
		printf("Я успешно миновал функцию ReadFromFile и вернулся в main\n");

		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	#endif
	
	int NumberOfStrings = DecomposeToIndex(&Index, &buffer);//разложит всё в индекс из буфера 

	#ifdef DEBAG
		printf("Я успешно миновал функцию DecomposeToIndex и вернулся в main\n");
	#endif

	//int NumberOfStrings = GetNumberOfStrings(buffer);

	#ifdef DEBAG
		printf("Я успешно миновал функцию GetNumberOfStrings, получил значение NumberOfStrings = %d\n", NumberOfStrings);
		printf("и нахожусь в main\n");
		PrintFile(Index, NumberOfStrings);//печатает файл(с помощью индекса)
		printf("распечатал файл до сортировки \n");
		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	#endif

	qsort(Index, NumberOfStrings, sizeof(MyString), CompareByFirstLetters);//сортровка первого варианта, тут индекс должен быть указателем на первый элемент
	
	#ifdef DEBAG
		printf("Я успешно миновал функцию qsort и вернулся в main\n");
	#endif

	PrintFile(Index, NumberOfStrings);//печатает файл(с помощью индекса)

	#ifdef DEBAG
		printf("Я успешно миновал функцию PrintFile, распечатал текст и вернулся в main\n");
	#endif
	
	PrintSeparator();//печатает разделитель
	
	#ifdef DEBAG
		printf("Я успешно миновал функцию PrintSeparator и вернулся в main\n");
	#endif
	
	Myqsort(Index, 0, NumberOfStrings - 1, CompareByLastLetters);//сортировка второго варианта

	#ifdef DEBAG
		printf("Я успешно миновал функцию Myqsort и вернулся в main\n");
	#endif

	PrintFile(Index, NumberOfStrings);//печатает файл

	#ifdef DEBAG
		printf("Я успешно миновал функцию PrintFile, распечатал текст и вернулся в main\n");
	#endif

	//выводить
	PrintSeparator();//печатает разделитель

	PrintBuffer(buffer);//печатает исходный файл, можно попробовать модифицировать printfile()

	FreeMemory(&Index, &buffer);

	#ifdef DEBAG
		printf("Я всё. Тут мои полномочия всё.\n");
	#endif

	return 0;
}
