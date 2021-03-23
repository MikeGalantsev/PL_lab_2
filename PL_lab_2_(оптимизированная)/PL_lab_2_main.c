#include "PL_lab_2_header.h"

Node* ABC = NULL; //словарь (стек)
char rebus[100] = { 0 }; //ребус
int abcTotal = 0; //количество букв в алфавите ребуса
Let ABCLettersOnly[10]; //словарь (только буквы)

int main(int argc, char** argv)
{
	if (argc != 2)
		return -1;
	clock_t time = clock();
	//переменные
	int abcCurrent = 0; //количество букв с заданными цифрами
	long long i, j, k;
	QUEUE Digits; //очередь цифр 9876543210
	Digits.queue_pHead = NULL;
	//заполнить очередь цифрами
	put(&Digits, 9);
	put(&Digits, 8);
	put(&Digits, 7);
	put(&Digits, 6);
	put(&Digits, 5);
	put(&Digits, 4);
	put(&Digits, 3);
	put(&Digits, 2);
	put(&Digits, 1);
	put(&Digits, 0);
	//скопировать и проанализировать ребус
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
		return -1;
	//заполнить словарь
	for (i = 0; rebus[i] != '\0'; i++)
	{
		if (rebus[i] == '+' || rebus[i] == '=')
			continue;
		for (j = 0; j < abcTotal; j++)
			if (rebus[i] == ABCLettersOnly[j].letter)
				break;
		if (j == abcTotal)
		{
			ABCLettersOnly[abcTotal].letter = rebus[i];
			if (rebus[i - 1] == '+' || i == 0 || rebus[i - 1] == '=')
				ABCLettersOnly[abcTotal].isCapital = 1;
			else
				ABCLettersOnly[abcTotal].isCapital = 0;
			abcTotal++;
		}
		else if (rebus[i - 1] == '+' || i == 0 || rebus[i - 1] == '=')
			ABCLettersOnly[j].isCapital = 1;
	}
	//перебор с возвратом
	int luck = 0;
	move(&abcCurrent, &Digits, &luck);
	//вывод ответа
	for (i = 0; rebus[i] != '\0'; i++)
	{
		if (rebus[i] == '+' || rebus[i] == '=')
		{
			printf("%c", rebus[i]);
			continue;
		}
		for (Node* p = ABC; p != NULL; p = p->pNext)
			if (rebus[i] == p->letter)
			{
				printf("%c", p->digit + '0');
				break;
			}
	}
	//освобождение выделенной памяти
	while (ABC)
		pop();
	while (Digits.queue_pHead)
		get(&Digits);
	time = clock() - time;
	printf("\ntime: %.16f sec\n\n", (float)time / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------
int MemoryError()
{
	printf("Memory error.\n");
	return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------
void push(char Letter, int Digit)
{
	if (ABC != NULL)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		if (p == NULL)
		{
			MemoryError();
			return;
		}
		p->letter = Letter;
		p->digit = Digit;
		p->pNext = ABC;
		ABC = p;
	}
	else
	{
		ABC = (struct Node*)malloc(sizeof(struct Node));
		if (ABC == NULL)
		{
			MemoryError();
			return;
		}
		ABC->letter = Letter;
		ABC->digit = Digit;
		ABC->pNext = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
int pop()
{
	Node* p = ABC;
	int num = p->digit;
	ABC = ABC->pNext;
	free(p);
	return num;
}

//-------------------------------------------------------------------------------------------------------------------------------
void put(QUEUE* Q, int num)
{
	if (Q->queue_pHead != NULL)
	{
		Q->queue_pTail->pNext = (List*)malloc(sizeof(List));
		if (Q->queue_pTail->pNext == NULL)
		{
			MemoryError();
			return;
		}
		Q->queue_pTail = Q->queue_pTail->pNext;
		Q->queue_pTail->digit = num;
		Q->queue_pTail->pNext = NULL;
	}
	else
	{
		Q->queue_pHead = (List*)malloc(sizeof(List));
		if (Q->queue_pHead == NULL)
		{
			MemoryError();
			return;
		}
		Q->queue_pHead->digit = num;
		Q->queue_pHead->pNext = NULL;
		Q->queue_pTail = Q->queue_pHead;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
int get(QUEUE* Q)
{
	List* p = Q->queue_pHead;
	int num = p->digit;
	Q->queue_pHead = Q->queue_pHead->pNext;
	free(p);
	return num;
}

//-------------------------------------------------------------------------------------------------------------------------------
int getCheck(QUEUE* Q)
{
	return Q->queue_pHead->digit;
}

//-------------------------------------------------------------------------------------------------------------------------------
_Bool IsSolution()
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
				for (Node* p = ABC; p != NULL; p = p->pNext)
					if (copy[j] == p->letter)
					{
						copy[j] = p->digit + '0';
						break;
					}
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

//-------------------------------------------------------------------------------------------------------------------------------
void move(int* abcCurrent, QUEUE* Digits, int* luck)
{
	int firstNum = getCheck(Digits);
	int num;
	do {
		num = get(Digits);
		if (ABCLettersOnly[*abcCurrent].isCapital && num == 0) //эвристика
		{
			put(Digits, num);
			continue;
		}
		else //подходит
		{
			push(ABCLettersOnly[*abcCurrent].letter, num);
			(*abcCurrent)++;
			if (*abcCurrent != abcTotal)
			{
				move(abcCurrent, Digits, luck);
				if (!(*luck))
				{
					put(Digits, pop());
					(*abcCurrent)--;
				}
			}
			else
			{
				if (IsSolution())
					*luck = 1;
				else
				{
					put(Digits, pop());
					(*abcCurrent)--;
				}
			}
		}
	} while (*luck == 0 && getCheck(Digits) != firstNum);
}