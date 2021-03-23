#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>

//��� �������
typedef struct Let
{
	char letter;
	_Bool isCapital;
} Let;

//��� �����
typedef struct Node
{
	char letter;
	int digit;
	struct Node* pNext;
} Node;

//��� �������
typedef struct List
{
	int digit;
	struct List* pNext;
} List;

//����� ������� (head) � ����� ������� (tail)
typedef struct QUEUE
{
	List* queue_pHead;
	List* queue_pTail;
} QUEUE;

//�������� ������� � ����
void push(char Letter, int Digit);

//������� ������� �� �����
int pop();

//�������� ������� � �������
void put(QUEUE* Q, int num);

//������� ������� �� �������
int get(QUEUE* Q);

//���������� �� ������ ������� �������
int getCheck(QUEUE* Q);

//������ ��������� ������
int MemoryError();

//�������� �������
_Bool IsSolution();

//������� ����������� ������� �������� � ���������
void move(int* abcCurrent, QUEUE* Digits, int* luck);