#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>

//структура для словаря
typedef struct Node
{
	char letter;
	int digit;
	_Bool isCapital;
} Node;

//Проверка на то, что в числе все цифры различны
_Bool IsDifferentDigits(long long num);

//Проверка решения
_Bool IsSolution(char* rebus, Node* ABC, int abcTotal);

//-------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if (argc != 2)
		return -1;
	clock_t time = clock();
	//переменные
	Node ABC[10] = { 0 }; //словарь
	int abcTotal = 0; //количество букв в алфавите ребуса
	long long i, j, k;
	//скопировать и проанализировать ребус
	char rebus[100] = { 0 }; //ребус
	for (i = 0, j = 0, k = 0; argv[1][i] != '\0'; i++)
	{
		if (argv[1][i] == '+')
			j++;
		else if (argv[1][i] == '=')
			k++;
		else if (argv[1][i] < 65 && argv[1][i] > 90) //проверка на буквы в верхнем регистре
			return -1;
		rebus[i] = argv[1][i];
	}
	//проверка на кол-во слагаемых от 2 до 7
	if (j < 1 || j > 6 || k != 1)
		return - 1;
	//заполнить словарь
	for (i = 0; rebus[i] != '\0'; i++)
	{
		if (rebus[i] == '+' || rebus[i] == '=')
			continue;
		for (j = 0; j < abcTotal; j++)
			if (rebus[i] == ABC[j].letter)
				break;
		if (j == abcTotal)
		{
			ABC[abcTotal].letter = rebus[i];
			ABC[abcTotal].digit = -1;
			if (i == 0 || rebus[i - 1] == '+' || rebus[i - 1] == '=')
				ABC[abcTotal].isCapital = 1;
			else
				ABC[abcTotal].isCapital = 0;
			abcTotal++;
		}
		else if (i == 0 || rebus[i - 1] == '+' || rebus[i - 1] == '=')
			ABC[j].isCapital = 1;
	}
	//подбор ответа
	long long start = 9876543210 / (long long)pow(10, 10 - abcTotal); //верхняя граница перебора
	long long end = 1023456789 / (long long)pow(10, 10 - abcTotal); //нижняя границы перебора
	long long copy;
	for (i = start; i >= end; i--)
	{
		if (!IsDifferentDigits(i))
			continue;
		copy = i;
		for (j = abcTotal - 1; j >= 0; j--)
		{
			ABC[j].digit = copy % 10;
			copy /= 10;
			if (ABC[j].isCapital && ABC[j].digit == 0)
				break;
		}
		if (j != -1)
			continue;
		if (IsSolution(rebus, ABC, abcTotal))
			break;
	}
	//вывод ответа
	for (i = 0; rebus[i] != '\0'; i++)
	{
		if (rebus[i] == '+' || rebus[i] == '=')
		{
			printf("%c", rebus[i]);
			continue;
		}
		for (j = 0; j < abcTotal; j++)
			if (rebus[i] == ABC[j].letter)
				printf("%c", ABC[j].digit + '0');
	}
	time = clock() - time;
	printf("\ntime: %.16f sec\n\n", (float)time / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------
_Bool IsDifferentDigits(long long num)
{
	int Arr[19];
	int N = 0;
	while (num)
	{
		Arr[N] = num % 10;
		num /= 10;
		N++;
	}
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
			if (Arr[i] == Arr[j])
				return 0;
	return 1;
}

//-------------------------------------------------------------------------------------------------------------------------------
_Bool IsSolution(char* rebus, Node* ABC, int abcTotal)
{
	char copy[100];
	unsigned int sum = 0, res;
	for (int i = 0, j = 0; ; i++)
	{
		if (rebus[i] >= 65 && rebus[i] <= 90)
			copy[j++] = rebus[i];
		else
		{
			copy[j] = '\0';
			for (j = 0; copy[j] != '\0'; j++)
				for (int k = 0; k < abcTotal; k++)
					if (copy[j] == ABC[k].letter)
						copy[j] = ABC[k].digit + '0';
			if (rebus[i] == '+' || rebus[i] == '=')
				sum += atoi(copy);
			else if (rebus[i] == '\0')
			{
				res = atoi(copy);
				if (sum == res)
					return 1;
				return 0;
			}
			j = 0;
		}
	}
}