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

void PrintGreetings();

int ReadFromFile(char **buffer_ptr, char* NameOfFile);
void DecomposeToIndex(MyString** Index_ptr, char **buffer_ptr);
int GetNumberOfStrings(char *buffer);
void PrintFile(MyString* Index,int NumberOfStrings);
void PrintSeparator();
void PrintBuffer(char *buffer);
int CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid);
int CompareByLastLetters(const void* OneStringVoid, const void* AnotherStringVoid);
void swap(MyString *Index, int i, int j);
void Myqsort(MyString *Index, int left, int right, int(*comparator)(const void *, const void *));
int GetSizeOfFile(FILE* FilePtr);

//int DeleteEmptyStrings(char *buffer, int NumberOfSymbols);


int main(int argc, char *argv[]) {

	PrintGreetings();//печатаем приветствие
	
	MyString *Index  = nullptr;//пока не знаем размер массива структур
	char     *buffer = nullptr;//будем читать туда файл

	#ifdef DEBAG
		printf("%s\n", argv[1]);
		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	#endif

	int NumberOfSymbols = ReadFromFile(&buffer, argv[1]);//записали весь файл в строку

	#ifdef DEBAG
		printf("Значение NumberOfSymbols равно = %d\n", NumberOfSymbols);
		if (buffer == nullptr)
			printf("buffer в функции main после ReadFromFile содержит нулевой указатель\n");
		if (buffer != nullptr) 
			printf("buffer в функции main после ReadFromFile содержит ненулевой указатель\n");
		printf("Я успешно миновал функцию ReadFromFile и вернулся в main\n");

		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	
	#endif

	//int NewNumberOfSymbols = DeleteEmptyStrings(buffer, NumberOfSymbols);
	#ifdef DEBAG
		printf("успешно миновал функцию DeleteEmptyStrings\n");
		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	#endif

	
	DecomposeToIndex(&Index, &buffer);//разложит всё в индекс из буфера 

	#ifdef DEBAG
		printf("Я успешно миновал функцию DecomposeToIndex и вернулся в main\n");
		
	#endif

	int NumberOfStrings = GetNumberOfStrings(buffer);
	#ifdef DEBAG
		printf("Я успешно миновал функцию GetNumberOfStrings, получил значение NumberOfStrings = %d\n", NumberOfStrings);
		printf("и нахожусь в main\n");
		PrintFile(Index, NumberOfStrings);//печатает файл(с помощью индекса)
		printf("распечатал файл до сортировки \n");
		PrintBuffer(buffer);
		printf("распечатал буфер\n");
	#endif

	qsort(Index, NumberOfStrings - 1, sizeof(MyString), CompareByFirstLetters);//сортровка первого варианта, тут индекс должен быть указателем на первый элемент
	
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
	free(Index);
	free(buffer);
	#ifdef DEBAG
		printf("Я всё. Тут мои полномочия всё.\n");
	#endif
	return 0;
}
/* уже вроде не надо
int CountSymbInfile(FILE* FilePtr){//берет поток ввода и считает количество символов вхождения
	через указатели на конец и начало файла, чекнуть керниган
	return QuantityOfSymbols;
}
*/


//норм, надо
int ReadFromFile(char **buffer_ptr,char* NameOfFile){//читает из файла и записывает в буффер
	#ifdef DEBAG
		printf("Я в функции ReadFromFile\n");
	#endif

	FILE*  FilePtr = fopen(NameOfFile, "r");//вернёт null если не удалось открыть

	if (FilePtr == NULL) {						
		printf("Error in funcion %s \n", __FUNCTION__);		//обработка ошибки
		return -1;
	}
	
	int NumberOfSymbols = 0;//nan нельзя??????
	int SizeOfFile = GetSizeOfFile(FilePtr);

	#ifdef DEBAG
		printf("я успешно миновал функцию GetSizeOfFile и нахожусь в функции ReadFromFile\n");
		printf("значение SizeOfFile = %d\n", SizeOfFile);
	#endif

	*buffer_ptr = (char *)calloc(SizeOfFile + 1, sizeof(char)); //выделяем память под буффер, + \0
	if (*buffer_ptr == NULL) {
		printf("Error in funcion %s \n", __FUNCTION__);
		return -1;
	}
	
	NumberOfSymbols = fread (*buffer_ptr, 1, SizeOfFile, FilePtr);

	if (NumberOfSymbols != SizeOfFile)
		printf("Error in funcion %s \n", __FUNCTION__);

	(*buffer_ptr)[SizeOfFile] = '\0'; //положили \0 в конце массива буффер
	#ifdef DEBUG 
		printf("Я в функции ReadFromFile положил 0 в буфер\n");
	#endif

	fclose(FilePtr);
	return NumberOfSymbols;//без \0
}
//норм, надо
void PrintSeparator() {//печатает разделитель
	printf("________________________________________________\n");
}
//вроде норм, надо
void PrintFile(MyString* Index,int NumberOfStrings){//печатает массив Index, index это массив структур
	#ifdef DEBUG
		printf("начала работу функция PrintFile\n");
	#endif
	if (Index == nullptr){
		printf("index is empty.\n");
		return;
	}

	for (int count = 0; count < NumberOfStrings; count++){ //печатаем пока не встретим /0
		for(int NumberOrElemInString = 0; Index[count].PtrOnStartOfString[NumberOrElemInString] != '\n'; NumberOrElemInString++)
		 printf("%c",Index[count].PtrOnStartOfString[NumberOrElemInString]);//было index[count]

		printf("\n");
		
	}
	#ifdef DEBUG
		printf("завершила работу функция PrintFile\n");
	#endif
}

//читаем до /0, заносим строку в отдельный массив буфер, так до конца файла, адресы начала строк записываем в индекс
//норм, надо
void PrintGreetings() { //печатает приветствие программы
	printf("This program sorts lines of text\n\n");
}
//норм
int GetSizeOfFile(FILE* FilePtr) {//определяеет размер файла
	fseek(FilePtr, 0, SEEK_END);//устанавливает индикатор на конец файла
	int SizeOfFile = ftell(FilePtr);//количество байтов, которые отделяют индикатор от начала файла
	rewind (FilePtr);//устанавливает индикатор обратно на начало файла

	return SizeOfFile;//это без \0 на конце
}

//** ptr
//разобраться с указателями, а так вроде ок, надо
void DecomposeToIndex(MyString** Index_ptr, char **buffer_ptr){//пробежится по буферу и заполнит индекс
	int NumberOfStrings = GetNumberOfStrings(*buffer_ptr);

	#ifdef DEBAG
		printf("Я нахожусь в DecomposeToIndex и успешно миновал функцию GetNumberOfStrings\n");
		printf("NumberOfStrings = %d\n", NumberOfStrings);
	#endif

	*Index_ptr = (MyString *)calloc(NumberOfStrings, sizeof(MyString));

	assert((*Index_ptr) != nullptr);
	int ind_flag = 0;//индекс, будет бежать по массиву индекс

	//тут точно верно звёздочки расположила??
	(*Index_ptr)[ind_flag].PtrOnStartOfString = *buffer_ptr;//в первый положили указатель на начало буффера
	int buf_flag = 0;
	for (buf_flag = 0;((*buffer_ptr)[buf_flag]) != '\0'; buf_flag++){//пройтись по всему буферу
		if ((*buffer_ptr)[buf_flag] == '\n'){
			while(isspace((*buffer_ptr)[buf_flag + 1])){//если несколько подряд идущих \n
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
}

//ну норм,
int GetNumberOfStrings(char *buffer){ //определяет сколько строк в буфере

	#ifdef DEBAG
		printf("1)Запущена функция GetNumberOfStrings\n");
	#endif

	int NumberOfStrings = 0; //изначально количество строк 0

	#ifdef DEBAG
		printf("2)Запущена функция GetNumberOfStrings\n");
	#endif

	if (buffer == nullptr){
		printf("buffer в функции GetNumberOfStrings содержит нулевой указатель\n");
		return -1;
	}

	#ifdef DEBAG
		printf("3)Запущена функция GetNumberOfStrings\n");
		printf("первый элемент буфера: %c\n", *buffer);
	#endif
		
	for (int count = 0; buffer[count] != '\0'; count++){
	
		if (buffer[count] == '\n')//нам вообще /0 нельзя использовать??
			NumberOfStrings++;//подряд идущие \т тоже строки
	}

	#ifdef DEBAG
		printf("миновал цикл в функции GetNumberOfStrings\n");
	#endif

	//NumberOfStrings++;//про запас уберем, чтобы не было пустых строк

	return NumberOfStrings;
} 


//65 66 вроде норм, надо
int CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid){//компараторы
	#ifdef DEBAG
		printf("начала работать функция CompareByFirstLetters\n");
	#endif

	const MyString *OneString     = (MyString *)OneStringVoid;		//привели к типу, чтобы можно было работать
	const MyString *AnotherString = (MyString *)AnotherStringVoid;

	#ifdef DEBAG
		printf("1) работает функция CompareByFirstLetters\n");
	#endif

	//проверить, не пустые ли это строки
	if (OneString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);

	#ifdef DEBAG
		printf("2) работает функция CompareByFirstLetters\n");
	#endif

	if (AnotherString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);

	#ifdef DEBAG
		printf("3) работает функция CompareByFirstLetters\n");
	#endif
	
	int OneStringElement     = 0;// будет ходить по первой строке
	int AnotherStringElement = 0; //будет ходить по второй строке

    //цикл пока не дойдёем до конца строки
	for (; OneStringElement < OneString->LenOfString && AnotherStringElement < AnotherString->LenOfString; OneStringElement++, AnotherStringElement++){
		//в обоих строках пропускаем знаки пунктуации и цифры
		while (ispunct(*(OneString->PtrOnStartOfString + OneStringElement))   || 
		  	   isdigit(*(OneString->PtrOnStartOfString + OneStringElement))){

			OneStringElement++;
		}
		while(ispunct(*(AnotherString->PtrOnStartOfString + AnotherStringElement)) ||
		  	  isdigit(*(AnotherString->PtrOnStartOfString + AnotherStringElement))){

			AnotherStringElement++;
		}
		//если не равны, то вернем разницу в Int
		if( (*(OneString    ->PtrOnStartOfString + OneStringElement    )) != 
			(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))

			return (int)(*(OneString    ->PtrOnStartOfString + OneStringElement)) - 
		           (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement));
	}

	#ifdef DEBAG
		printf(" закончила работать функция CompareByFirstLetters\n");
	#endif

	//если все же дошли до конца строк, выводим ту что короче
	return (int)(*(OneString    ->PtrOnStartOfString + OneStringElement)) -
	       (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement));


	
}
//норм, надо

int CompareByLastLetters(const void* OneStringVoid, const void* AnotherStringVoid){

	const MyString *OneString     = (MyString *)OneStringVoid;			//приводим к типу, чтобы можно было работать
	const MyString *AnotherString = (MyString *)AnotherStringVoid;

	#ifdef DEBAG
		printf("CompareByLastLetters");
	#endif

	//проверить, не пустые ли это строки
	if (OneString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);
	if (AnotherString->PtrOnStartOfString == nullptr)
		printf("Error in funcion %s \n", __FUNCTION__);

	int OneStringElement     = OneString    ->LenOfString - 1; //будет ходить по первой строке c конца
	int AnotherStringElement = AnotherString->LenOfString - 1; //будет ходить по второй строке с конца

//цикл пока не дойдёем до начала строки
	for (; OneStringElement > 0 && AnotherStringElement > 0; --OneStringElement, --AnotherStringElement){
		//в обоих строках пропускаем знаки пунктуации и цифры
		while (ispunct(*(OneString->PtrOnStartOfString + OneStringElement))   || 
		  	   isdigit(*(OneString->PtrOnStartOfString + OneStringElement))){

			OneStringElement--;
		}
		while(ispunct(*(AnotherString->PtrOnStartOfString + AnotherStringElement)) ||
		  	  isdigit(*(AnotherString->PtrOnStartOfString + AnotherStringElement))){

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


//норм мейби
void PrintBuffer(char *buffer){//печатает буффер
	if (buffer == nullptr){
		printf("buffer is empty.\n");
		return;
	}
	printf("%s\n", buffer);
}


void Myqsort(MyString *Index, int left, int right, int(*comparator)(const void *,const void *)){
	int i, last;
	//void swap(void *v[], int i, int j);

	if (left >= right)//если из одного элемента
		return;
	swap(Index, left, (left+right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ( ( (*comparator)((void *)&Index[i],(void *)&Index[left]) ) < 0 )
			swap(Index, ++last, i);
	swap(Index, left, last);
	Myqsort(Index, left, last-1, comparator);
	Myqsort(Index, last + 1, right, comparator);
}

void swap(MyString *Index, int i, int j) {
	MyString temp;

	temp = Index[i];
	Index[i] = Index[j];
	Index[j] = temp;
}
/*
int DeleteEmptyStrings(char *buffer, int NumberOfSymbols){//убирает повторяющиеся \n
	int old_num = 0;//пройдется по всему массиву буфер
	int new_num = 0;//будет записывать только не повторяющиеся \n
	#ifdef DEBAG
		printf("NumberOfSymbols in func DeleteEmptyStrings = %d\n", NumberOfSymbols);
	#endif
	while( old_num < NumberOfSymbols - 1){
		if (buffer[old_num] != '\n'){
			char tmp = buffer[old_num];
			buffer[new_num] = tmp;
			//buffer[new_num] = buffer[old_num];
			old_num++;
			new_num++;
		} 
		else if (buffer[old_num] == '\n' && buffer[old_num + 1] == '\n' ){
			old_num++;
		}
		else {
			//buffer[new_num] = buffer[old_num];
			char tmp = buffer[old_num];
			buffer[new_num] = tmp;
			old_num++;
			new_num++;

		}

	}
	buffer[new_num] == '\0';
	return new_num + 1;
}

*/

