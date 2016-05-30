#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define NUM_OF_ITEM_IN_DIET 4

#define MAX_STR 1000
#define MAX_NUM_OF_DATE 8 
#define MAX_NUM_OF_SELECTED_MEAL 4
#define MAX_NUM_OF_MEAL 200
#define MAX_NUM_OF_REVIEW 200
#define MAX_NUM_OF_SELECTED_MEAL_NUM 2
const char* printRecordMenu[NUM_OF_ITEM_IN_DIET] = { "��¥�� �Է��� �ּ���\n",
"[1.��ħ 2.���� 3.���� 4.����]�߿� � ���̾�����?\n",
"�������� �����ּ���.\n",
"�ݼ��� �Է��� �ּ���.\n" };


enum
{
	KIND_DATA_DATE,
	KIND_DATA_SELECTED_MEAL,
	KIND_DATA_SELECTED_MEAL_NUM,
	KIND_DATA_MEAL,
	KIND_DATA_REVIEW
	
} KIND_DATA;

typedef struct dietLinked
{
	char date[MAX_NUM_OF_DATE + 1]; //��¥
	char selectedMeal[MAX_NUM_OF_SELECTED_MEAL + 1]; //��ħ,����,����,����
	char meal[MAX_NUM_OF_MEAL + 1]; //������
	char review[MAX_NUM_OF_REVIEW + 1]; //�ݼ�
	char selectedMealNum[MAX_NUM_OF_SELECTED_MEAL_NUM +1];
	
	struct dietLinked* next;
	struct dietLinked* prev;
}DietL;

typedef struct listOfDietOnmemory
{
	int numOfNode;

	struct dietLinked* head;
	struct dietLinked* tail;
}List;