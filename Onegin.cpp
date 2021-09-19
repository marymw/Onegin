#include <stdio.h>
#include <stdlib.h>

/* ЕВГЕНИЙ ОНЕГИН */

//один раз прочитать файл(с пунктуацией, но убрать лишние пробелы)
//отсортировать в алфавитном порядке с помощью qsort()
//вывести
//сравнивать строки в обратном порядке с помощью собственной функции сортировки, с таким же компаратором как у qsort
//вывести
//вывести в исходном порядке
//

struct MyString {
	char *PtrOnStartOfString = nullptr;
	int   LenOfString        = NAN;
};

void PrintGreetings();
int ReadFromFile(char *buffer, const char* NameOfFile);
void DecomposeToIndex(MyString* Index, char *buffer);
int GetNumberOfStrings(char *buffer);
void PrintFile(MyString* Index,int NumberOfStrings);
void PrintSeparator();
void PrintBuffer(char *buffer);


int main(int argc, char *argv[]) {
	PrintGreetings();//печатаем приветствие
	
	MyString *Index  = nullptr;//пока не знаем размер массива структур
	char     *buffer = nullptr;//будем читать туда файл

	int NumberOfSymbols = ReadFromFile(buffer, argv[1]);//записали весь файл в строку
	
	DecomposeToIndex(Index, buffer);//разложит всё в индекс из буфера 

	int NumberOfStrings = GetNumberOfStrings(buffer);
	qsort(Index, NumberOfStrings, sizeof(MyString), CompareByFirstLetters);//сортровка первого варианта, тут индекс должен быть указателем на первый элемент
	
	PrintFile(Index, NumberOfStrings);//печатает файл(с помощью индекса)
	PrintSeparator();//печатает разделитель

	Myqsort(Index, 0, NumberOfStrings, CompareByLastLetters);//сортировка второго варианта
	PrintFile(Index, NumberOfStrings);//печатает файл

	//выводить
	PrintBuffer(buffer);//печатает исходный файл, можно попробовать модифицировать printfile()
	free(Index);
	free(buffer);
	return 0;
}
/* уже вроде не надо
int CountSymbInfile(FILE* FilePtr){//берет поток ввода и считает количество символов вхождения
	через указатели на конец и начало файла, чекнуть керниган
	return QuantityOfSymbols;
}
*/


//норм, надо
int ReadFromFile(char *buffer, const char* NameOfFile){//читает из файла и записывает в буффер
	FILE*  FilePtr = fopen(NameOfFile, "r");//вернёт null если не удалось открыть
	if (FilePtr == NULL) 						
		printf("Error in %s", ___FUNCTION__);		//обработка ошибки
	return;
	
	int NumberOfSymbols = NUN;
	int SizeOfFile = GetSizeOfFile(FilePtr);

	buffer = (char *)calloc(SizeOfFile, sizeof(char)); //выделяем память под буффер
	if (buffer == NULL) {
		printf("Error in %s\n", ___FUNCTION__);
		return;
	}

	
	NumberOfSymbols = fread (buffer, 1, SizeOfFile, FilePtr);
	if (NumberOfSymbols != SizeOfFile)
		printf("Error in %s\n", ___FUNCTION__);


	fclose(FilePtr);
	return NumberOfSymbols;
}
//норм, надо
void PrintSeparator() {//печатает разделитель
	printf("________________________________________________\n");
}
//вроде норм, надо
void PrintFile(MyString* Index,int NumberOfStrings){//печатает массив Index, index это массив структур

	for (int count = 0; count < NumberOfStrings; count++) 
		printf("%s\n",Index[count].PtrOnStartOfString);
}

//читаем до /0, заносим строку в отдельный массив буфер, так до конца файла, адресы начала строк записываем в индекс
//норм, надо
void PrintGreetings() { //печатает приветствие программы
	printf("This program sorts lines of text\n\n");
}
/*/норм, но не надо вроде
int GetSizeOfFile(FILE* FilePtr) {//определяеет размер файла
	fseek(FilePtr, 0, SEEK_END);//устанавливает индикатор на конец файла
	int SizeOfFile = ftell(FilePtr);//количество байтов, которые отделяют индикатор от начала файла
	rewind (FilePtr);//устанавливает индикатор обратно на начало файла

	return SizeOfFile;
}
*/

//разобраться с указателями, а так вроде ок, надо
void DecomposeToIndex(MyString* Index, char *buffer){//пробежится по буферу и заполнит индекс
	NumberOfStrings = GetNumberOfStrings(buffer);
	Index = calloc(NumberOfStrings, sizeof(MyString));
	int ind_flag = 0;//индекс, будет бежать по массиву индекс
	Index[ind_flag].PtrOnStartOfString = buffer;//в первый положили указатель на начало буффера

	for (int buf_flag = 0; buffer[buf_flag] != EOF; buf_flag++){//пройтись по всему буферу
		if (buffer[buf_flag] == '\n'){
			while(buffer[buf_flag + 1] == '\n'){//если несколько подряд идущих \n
				buf_flag++;
			}
			if (buffer[buf_flag + 1] != EOF){
				Index[ind_flag + 1].PtrOnStartOfString = *(buffer[buf_flag + 1]);//положили указатель на начало следующей строки в следующий элеент индекса
				Index[ind_flag].LenOfString = Index[ind_flag + 1].PtrOnStartOfString - Index[ind_flag].PtrOnStartOfString;//длина строки как разность указателей на начала строк
				ind_flag++;//можно потом засунуть в условие цикла
			}
			else //для самой последней строки
				Index[ind_flag].LenOfString = *(buffer[buf_flag + 1]) - Index[ind_flag].PtrOnStartOfString;
		}
		
	}
}

/*/ну норм, но не надо вроде
int GetNumberOfStrings(char *buffer){ //определяет сколько строк в буфере
	int NumberOfStrings = 0; //изначально количество строк 0
	for (int count = 0; buffer[count] != EOF; count++){
		if (buffer[count] == '\n')//нам вообще /0 нельзя использовать??
			NumberOfStrings++;//подряд идущие \т тоже строки
	}

	NumberOfStrings++;//про запас

	return NumberOfStrings;
} */


//65 66 вроде норм, надо
int CompareByFirstLetters(const void* OneStringVoid, const void* AnotherStringVoid){//компараторы
	const MyString *OneString     = (MyString *)OneStringVoid;		//привели к типу, чтобы можно было работать
	const MyString *AnotherString = (MyString *)AnotherStringVoid;

	//проверить, не пустые ли это строки
	if (OneString->PtrOnStartOfString == nullptr)
		printf("Error in %s\n", ___FUNCTION__);
	if (AnotherString->PtrOnStartOfString == nullptr)
		printf("Error in %s\n", ___FUNCTION__);

	
	int OneStringElement     = 0;// будет ходить по первой строке
	int AnotherStringElement = 0; //будет ходить по второй строке

    //цикл пока не дойдёем до конца строки
	for (; OneStringElement < OneString->LenOfString && AnotherStringElement < AnotherString->LenOfString; OneStringElement++, AnotherStringElement++){
		//в обоих строках пропускаем знаки пунктуации и цифры
		while (ispunct(*(OneString->PtrOnStartOfString + OneStringElement))   || 
		  	   isdigit(*(OneString->PtrOnStartOfString + OneStringElement))){

			OneStringElement++;
		}
		while(ispunct(*(AnotherString->PtrOnStartOfString + AnotherStringElement))
		  	  isdigit(*(AnotherString->PtrOnStartOfString + AnotherStringElement))){

			AnotherStringElement++;
		}
		//если не равны, то вернем разницу в Int
		if( (*(OneString->PtrOnStartOfString + OneStringElement)) != (*(AnotherString->PtrOnStartOfString + AnotherStringElement)))
			return (int)(*(OneString->PtrOnStartOfString + OneStringElement)) - (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))
	}

	//если все же дошли до конца строк, выводим ту что короче
	return (int)(*(OneString->PtrOnStartOfString + OneStringElement)) - (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))
	
}
//норм, надо
int CompareByLastLetters(const void* OneStringVoid, const void* AnotherStringVoid){

	const MyString *OneString     = (MyString *)OneStringVoid;			//приводим к типу, чтобы можно было работать
	const MyString *AnotherString = (MyString *)AnotherStringVoid;

	//проверить, не пустые ли это строки
	if (OneString->PtrOnStartOfString == nullptr)
		printf("Error in %s\n", ___FUNCTION__);
	if (AnotherString->PtrOnStartOfString == nullptr)
		printf("Error in %s\n", ___FUNCTION__);

	int OneStringElement     = OneString    ->LenOfString; //будет ходить по первой строке c конца
	int AnotherStringElement = AnotherString->LenOfString; //будет ходить по второй строке с конца

//цикл пока не дойдёем до начала строки
	for (; OneStringElement > 0 && AnotherStringElement > 0; OneStringElement--, AnotherStringElement--){
		//в обоих строках пропускаем знаки пунктуации и цифры
		while (ispunct(*(OneString->PtrOnStartOfString + OneStringElement))   || 
		  	   isdigit(*(OneString->PtrOnStartOfString + OneStringElement))){

			OneStringElement--;
		}
		while(ispunct(*(AnotherString->PtrOnStartOfString + AnotherStringElement))
		  	  isdigit(*(AnotherString->PtrOnStartOfString + AnotherStringElement))){

			AnotherStringElement--;
		}
		//если не равны, то вернем разницу в Int
		if( (*(OneString->PtrOnStartOfString + OneStringElement)) != (*(AnotherString->PtrOnStartOfString + AnotherStringElement)))
			return (int)(*(OneString->PtrOnStartOfString + OneStringElement)) - (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))
	}

	//если все же дошли до начала строк
	return (int)(*(OneString->PtrOnStartOfString + OneStringElement)) - (int)(*(AnotherString->PtrOnStartOfString + AnotherStringElement)))

}
/* не надо
int DoLetterSmall (char Letter) {//возвращает код прописной буквы
	int LetterCode = (int)Letter;
	if (LetterCode > 97)
		return LetterCode;
	else return LetterCode + 32;
}

int GetSymbolCode(char Symbol){ //возвращает ascii код символа
	int SymbolCode = (int)Symbol;
	return SymbolCode;
}
*/
//норм мейби
void PrintBuffer(char *buffer){//печатает буффер
	printf("%s\n", buffer);
}


void Myqsort(MyString *Index, int left, int right, int(*comparator)(const void *, const void *)){
	int i, last;
	//void swap(void *v[], int i, int j);

	if (left >= right)//если из одного элемента
		return;
	swap(Index, left, (left+right)/2);//на всякий случай
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comparator)(Index[i], Index[left]) < 0)
			swap(Index, ++last, i);
	swap(Index, left, last);
	Myqsort(v, left, last-1, comparator);
	Myqsort(v, last + 1, right, comparator);
}

void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}




//assert чем-то лучше if?
