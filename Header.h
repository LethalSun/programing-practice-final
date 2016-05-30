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
const char* printRecordMenu[NUM_OF_ITEM_IN_DIET] = { "날짜를 입력해 주세여\n",
"[1.아침 2.점심 3.저녁 4.간식]중에 어떤 것이었나요?\n",
"먹은것을 적어주세요.\n",
"반성을 입력해 주세요.\n" };


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
	char date[MAX_NUM_OF_DATE + 1]; //날짜
	char selectedMeal[MAX_NUM_OF_SELECTED_MEAL + 1]; //아침,점심,저녁,간식
	char meal[MAX_NUM_OF_MEAL + 1]; //먹은것
	char review[MAX_NUM_OF_REVIEW + 1]; //반성
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