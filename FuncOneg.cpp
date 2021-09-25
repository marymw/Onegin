#include "NewOneg.h"
#include <ctype.h>

void ReadFromFile(char **buffer_ptr, char* NameOfFile){			//читает из файла и записывает в буффер

	assert(NameOfFile);

	DEBUG_PRINTF("Я в функции ReadFromFile\n");

	FILE*  FilePtr = fopen(NameOfFile, "r");					//вернёт null если не удалось открыть
	assert(FilePtr);
	
	int SizeOfFile = GetSizeOfFile(FilePtr);		    		//это без \0

	DEBUG_PRINTF        ("я успешно миновал функцию GetSizeOfFile и нахожусь в функции ReadFromFile\n");
	DEBUG_PRINTF_ONE_ARG("значение SizeOfFile = %d\n", SizeOfFile);

	*buffer_ptr = (char *)calloc(SizeOfFile + 1, sizeof(char)); //выделяем память под буффер, + \0
	assert(*buffer_ptr); 
	
	size_t StatusFread = fread (*buffer_ptr, 1, SizeOfFile, FilePtr);
	assert(StatusFread == SizeOfFile);

	(*buffer_ptr)[SizeOfFile] = '\0';             				//положили \0 в конце массива буффер

	DEBUG_PRINTF("Я в функции ReadFromFile положил 0 в буфер\n");

	fclose(FilePtr);
}

void PrintSeparator(FILE *OutputFilePtr){						//печатает разделитель

	fprintf(OutputFilePtr, "\n\n\n");

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 15; j++)
			fprintf(OutputFilePtr, "*******");

		fprintf(OutputFilePtr, "\n");
	}
}

void PrintFile(MyString* Index, const int NumberOfStrings){			//печатает массив Index, index это массив структур

	DEBUG_PRINTF("начала работу функция PrintFile\n");

	if (Index == nullptr){
		printf("index is empty.\n");
		return;
	}

	for (int count = 0; count < NumberOfStrings; count++){ 		//печатаем пока не встретим /0

		for(int NumberOfElemInString = 0; 
			Index[count].PtrOnStartOfString[NumberOfElemInString] != '\n'; 
			NumberOfElemInString++)
//ЗАМЕНА НА ФРАЙТ
			printf("%c",Index[count].PtrOnStartOfString[NumberOfElemInString]);//было index[count]

		printf("\n");
		
	}
		DEBUG_PRINTF("завершила работу функция PrintFile\n");
}


void PrintGreetings() {											 //печатает приветствие программы

	printf("This program sorts lines of text\n\n");
}


int GetSizeOfFile(FILE* FilePtr) {								//определяеет размер файла

	fseek(FilePtr, 0, SEEK_END);								//устанавливает индикатор на конец файла
	int SizeOfFile = ftell(FilePtr);							//количество байтов от начала файла
	rewind(FilePtr);											//устанавливает индикатор обратно на начало файла

	return SizeOfFile;											//это без \0 на конце
}


int DecomposeToIndex(MyString** Index_ptr, char **buffer_ptr){	//пробежится по буферу и заполнит индекс

	int NumberOfStrings = GetNumberOfStrings(*buffer_ptr);		//будет возвращать колво строк

	DEBUG_PRINTF("Я нахожусь в DecomposeToIndex и успешно миновал функцию GetNumberOfStrings\n");
	DEBUG_PRINTF_ONE_ARG("NumberOfStrings = %d\n", NumberOfStrings);

	*Index_ptr = (MyString *)calloc(NumberOfStrings, sizeof(MyString));

	assert((*Index_ptr) != nullptr);

	int ind_flag = 0;											     //индекс, будет бежать по массиву индекс
			
	(*Index_ptr)[ind_flag].PtrOnStartOfString = *buffer_ptr;		 //в первый положили указатель на начало буффера

	int buf_flag = 0;

	for (buf_flag = 0;((*buffer_ptr)[buf_flag]) != '\0'; buf_flag++){ //пройтись по всему буферу

		if ((*buffer_ptr)[buf_flag] == '\n'){

			while(isspace((*buffer_ptr)[buf_flag + 1])){			  //если несколько подряд идущих \n
				buf_flag++;
			}

			if ((*buffer_ptr)[buf_flag + 1] != '\0'){

				(*Index_ptr)[ind_flag + 1].PtrOnStartOfString = *buffer_ptr + buf_flag + 1;//положили указатель на начало следующей строки в следующий элеент индекса
				(*Index_ptr)[ind_flag].LenOfString = (*Index_ptr)[ind_flag + 1].PtrOnStartOfString - (*Index_ptr)[ind_flag].PtrOnStartOfString;//длина строки как разность указателей на начала строк
				ind_flag++;//можно потом засунуть в условие цикла
			}

			else //для самой последней строки
				(*Index_ptr)[ind_flag].LenOfString = *buffer_ptr + buf_flag + 1 - (*Index_ptr)[ind_flag].PtrOnStartOfString;
		}
	}

	#ifdef DEBUG
		printf("буффер: адрес начала = %p\n", *buffer_ptr);

		for (int i = 0; i < NumberOfStrings; i++){
			printf("строка номер %d : адрес начала = %p, длина %zu\n", i, (*Index_ptr)[i].PtrOnStartOfString, (*Index_ptr)[i].LenOfString);
		}
	#endif

	return NumberOfStrings;
}

int GetNumberOfStrings(const char *buffer){ //определяет сколько ненулевых строк в буфере

	DEBUG_PRINTF("1)Запущена функция GetNumberOfStrings\n");

	int NumberOfStrings = 0; //изначально количество строк 0

	DEBUG_PRINTF("2)Запущена функция GetNumberOfStrings\n");

	if (buffer == nullptr){
		printf("buffer в функции GetNumberOfStrings содержит нулевой указатель\n");
		return -1;
	}

	DEBUG_PRINTF("3)Запущена функция GetNumberOfStrings\n");
	DEBUG_PRINTF_ONE_ARG("первый элемент буфера: %c\n", *buffer);
		
	for (int count = 0; buffer[count] != '\0'; count++){
	
		if (buffer[count] == '\n' && buffer[count + 1] != '\n')//нам вообще /0 нельзя использовать??
			NumberOfStrings++;//подряд идущие \т тоже строки
	}

	DEBUG_PRINTF        ("миновал цикл в функции GetNumberOfStrings\n");
	DEBUG_PRINTF_ONE_ARG("COUNT_OF_STRING = %d\n", NumberOfStrings);

	return NumberOfStrings;
} 



int CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid){//компараторы

	DEBUG_PRINTF("начала работать функция CompareByFirstLetters\n");

	const MyString *OneString     = (MyString *)OneStringVoid;		//привели к типу, чтобы можно было работать
	const MyString *AnotherString = (MyString *)AnotherStringVoid;

	DEBUG_PRINTF("1) работает функция CompareByFirstLetters\n");

	//проверить, не пустые ли это строки
	if (OneString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);

	DEBUG_PRINTF("2) работает функция CompareByFirstLetters\n");

	if (AnotherString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);

	DEBUG_PRINTF("3) работает функция CompareByFirstLetters\n");
	
	int OneStringElement     = 0;// будет ходить по первой строке
	int AnotherStringElement = 0; //будет ходить по второй строке

    //цикл пока не дойдёем до конца строки
	for (; OneStringElement < OneString->LenOfString && AnotherStringElement < AnotherString->LenOfString; OneStringElement++, AnotherStringElement++){
		//в обоих строках пропускаем знаки пунктуации и цифры
		while (ispunct(*(OneString->PtrOnStartOfString + OneStringElement))   || 
		  	   isdigit(*(OneString->PtrOnStartOfString + OneStringElement)) || 
		  	   (int)*(OneString->PtrOnStartOfString + OneStringElement) == -85){

			OneStringElement++;
		}
		while(ispunct(*(AnotherString->PtrOnStartOfString + AnotherStringElement)) ||
		  	  isdigit(*(AnotherString->PtrOnStartOfString + AnotherStringElement)) ||
		  	  (int)*(AnotherString->PtrOnStartOfString + AnotherStringElement) == -85){

			AnotherStringElement++;
		}
		//если не равны, то вернем разницу в Int
		if( (*(OneString    ->PtrOnStartOfString + OneStringElement    )) != 
			(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))

			return (int)(*(OneString    ->PtrOnStartOfString + OneStringElement)) - 
		           (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement));
	}

	DEBUG_PRINTF(" закончила работать функция CompareByFirstLetters\n");

	//если все же дошли до конца строк, выводим ту что короче
	return (int)(*(OneString    ->PtrOnStartOfString + OneStringElement)) -
	       (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement));


	
}

int CompareByLastLetters(const void* OneStringVoid, const void* AnotherStringVoid){

	const MyString *OneString     = (MyString *)OneStringVoid;			//приводим к типу, чтобы можно было работать
	const MyString *AnotherString = (MyString *)AnotherStringVoid;

	DEBUG_PRINTF("CompareByLastLetters\n");

	//проверить, не пустые ли это строки
	if (OneString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);
	if (AnotherString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);

	int OneStringElement     = OneString    ->LenOfString - 1 ; //будет ходить по первой строке c конца
	int AnotherStringElement = AnotherString->LenOfString - 1 ; //будет ходить по второй строке с конца

//цикл пока не дойдёем до начала строки
	for (; OneStringElement > 0 && AnotherStringElement > 0; --OneStringElement, --AnotherStringElement){
		//в обоих строках пропускаем знаки пунктуации и цифры иии всякие лишние /n
		while (ispunct(*(OneString->PtrOnStartOfString + OneStringElement))   || 
		  	   isdigit(*(OneString->PtrOnStartOfString + OneStringElement))   ||
		  	          (*(OneString->PtrOnStartOfString + OneStringElement) == '\n') ){

			OneStringElement--;
		}
		while(ispunct(*(AnotherString->PtrOnStartOfString + AnotherStringElement)) ||
		  	  isdigit(*(AnotherString->PtrOnStartOfString + AnotherStringElement)) ||
		  	  		 (*(AnotherString->PtrOnStartOfString + AnotherStringElement) == '\n')){

			AnotherStringElement--;
		}
		//если не равны, то вернем разницу в Int
		if( (*(OneString    ->PtrOnStartOfString + OneStringElement)) != 
			(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))

			return (int)(*(OneString    ->PtrOnStartOfString + OneStringElement)) - 
		           (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement));
	}

	//если все же дошли до начала строк
	return (int)(*(OneString    ->PtrOnStartOfString + OneStringElement)) - 
	       (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement));


}

void PrintBuffer(const char *buffer){//печатает буффер в терминал

	if (buffer == nullptr){
		printf("buffer is empty.\n");
		return;
	}
	printf("%s\n", buffer);
}


void Myqsort(MyString *Index, int left, int right, int(*comparator)(const void *,const void *)){

	int i = 0, last = 0;

	if (left >= right)//если из одного элемента
		return;
	swap(Index, left, (left+right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ( ( (*comparator)((void *)&Index[i],(void *)&Index[left]) ) < 0 )
			swap(Index, ++last, i);
	swap(Index, left, last);
	Myqsort(Index, left, last - 1, comparator);
	Myqsort(Index, last + 1, right, comparator);
}
//const
void swap(MyString *Index, const int i, const int j) {
	MyString temp = {};

	temp = Index[i];
	Index[i] = Index[j];
	Index[j] = temp;
}


void PrintToFile(FILE*  OutputFilePtr, MyString *Index, const int NumberOfStrings){//печатает индекс в файл

	assert(Index);

	for (int count = 0; count < NumberOfStrings; count++){
		size_t StatusOfFwrite = fwrite(Index[count].PtrOnStartOfString, sizeof(char), Index[count].LenOfString, OutputFilePtr);
		if (StatusOfFwrite != Index[count].LenOfString)
			printf("Error in funcion %s\n", __FUNCTION__);

	}
	
}

FILE* OpenOutputFile(char* NameOfOutputFile){//открывает файл для записи

	FILE*  OutputFilePtr = fopen(NameOfOutputFile, "w");//вернёт null если не удалось открыть
	assert(OutputFilePtr);

	return OutputFilePtr;
}

void PrintGoodBye(){
	printf("Я всё. Тут мои полномочия всё.\n");
}

void PrintBufferToFile(FILE*  OutputFilePtr, const char *buffer){
	if (buffer == nullptr){
		printf("buffer is empty.\n");
		return;
	}

	fprintf(OutputFilePtr, "%s\n", buffer);
}

int CloseOutputFile(FILE*  OutputFilePtr){
	int StatusOfCloseFile = fclose(OutputFilePtr);

	if (StatusOfCloseFile != 0){
		printf("Ошибка закрытия файла\n");
		return StatusOfCloseFile;
	}
	return StatusOfCloseFile;
}
	

int ArgCheck(int argc){

	switch (argc){
		case 1:
			printf("Ошибка ввода файлов ввода и вывода. Проверьте наличие файлов для ввода и вывода\n");
			return NOINPUTFILE;
		case 2:
			printf("Ошибка вывода. Проверьте наличие файла вывода.\n");
			return NOOUTPUTFILE;
		case 3:
			printf("Всё прекрасно! Запускаем программу....\n\n");
			return NOERRORS;
		default:
			printf("Too many arguments!\n");
			return TOOMANYARGS;
	}

	return NOERRORS;
}
