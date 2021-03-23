#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>

//Для словаря
typedef struct Let
{
	char letter;
	_Bool isCapital;
} Let;

//Для стека
typedef struct Node
{
	char letter;
	int digit;
	struct Node* pNext;
} Node;

//Для очереди
typedef struct List
{
	int digit;
	struct List* pNext;
} List;

//глава очереди (head) и хвост очереди (tail)
typedef struct QUEUE
{
	List* queue_pHead;
	List* queue_pTail;
} QUEUE;

//добавить элемент в стек
void push(char Letter, int Digit);

//забрать элемент из стека
int pop();

//добавить элемент в очередь
void put(QUEUE* Q, int num);

//забрать элемент из очереди
int get(QUEUE* Q);

//посмотреть на первый элемент очереди
int getCheck(QUEUE* Q);

//Ошибка выделения памяти
int MemoryError();

//Проверка решения
_Bool IsSolution();

//главная рекурсивная функция перебора с возвратом
void move(int* abcCurrent, QUEUE* Digits, int* luck);