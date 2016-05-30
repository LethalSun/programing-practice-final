#include "Header.h"

List* listOfDietOnmemory;

// data.txt에 저장하는 함수.
int writeDataToFile()
{
	FILE* fp;
	char delimeter = 21;
	DietL* curNode;
	if (listOfDietOnmemory->head == NULL)
	{
		return -1;
	}

	fp = fopen("data.txt", "w");
	if (fp == NULL)

	{

		return -2;

	}
	
	curNode = listOfDietOnmemory->head;


	do
	{
		fprintf(fp,"%s%c%s%c%s%c%s%c%s\n",curNode->date, delimeter,curNode->selectedMeal,
			delimeter,curNode->selectedMealNum,delimeter,curNode->meal,delimeter,curNode->review);
		curNode = curNode->next;
	} while (curNode != NULL);

	fclose(fp);

	return 0;
}

//데이터파일에서 한줄씩 읽어온 데이터를 delimeter로 잘라서 구조체에 넣는 함수
int cutStr(char *str, DietL* temp)
{
	int i = 0;
	int j = 0;
	int preI = -1;
	int item = -1;

	while (str[i] != NULL)
	{
		if (str[i] == 21 || str[i] == '\n')
		{
			item++;

			switch (item)
			{
			case KIND_DATA_DATE:
			{
				for (j = 0; j < (i - preI); j++)
				{
					//이부분 수정 필요 아침부터 들어감.
					temp->date[j] = str[preI + j + 1];
				}
				temp->date[MAX_NUM_OF_DATE] = '\0';
				break;
			}
			case KIND_DATA_SELECTED_MEAL:
			{
				for (j = 0; j < (i - preI); j++)
				{
					temp->selectedMeal[j] = str[preI + j + 1];
				}
				temp->selectedMeal[MAX_NUM_OF_SELECTED_MEAL] = '\0';
				break;
			}
			//아침 점심 저녁 순으로 정렬하기 위한 번호
			case KIND_DATA_SELECTED_MEAL_NUM:
			{
				for (j = 0; j < (i - preI); j++)
				{
					temp->selectedMealNum[j] = str[preI + j + 1];
				}
				temp->selectedMealNum[i - preI - 1] = '\0';
				break;
			}
			case KIND_DATA_MEAL:
			{
				for (j = 0; j < (i - preI); j++)
				{
					temp->meal[j] = str[preI + j + 1];
				}
				temp->meal[i - preI - 1] = '\0';
				break;
			}
			case KIND_DATA_REVIEW:
			{
				for (j = 0; j < (i - preI); j++)
				{
					temp->review[j] = str[preI + j + 1];
				}
				temp->review[i - preI - 1] = '\0';
				break;
			}

			default:
				break;
			}
			preI = i;
		}
		i++;
	}

}
//식단을 입력 받는 함수.
int getNewDataFromUser()
{
	int i = 0;
	int j;
	int length = 0;
	int inputForSelectedMeal;
	char breakfast[MAX_NUM_OF_SELECTED_MEAL + 1] = "아침";
	char lunch[MAX_NUM_OF_SELECTED_MEAL + 1] = "점심";
	char dinner[MAX_NUM_OF_SELECTED_MEAL + 1] = "저녁";
	char snack[MAX_NUM_OF_SELECTED_MEAL + 1] = "간식";

	DietL* recordDiet = (DietL*)malloc(sizeof(DietL));
	if (recordDiet == NULL)
	{
		return -1;
	}

	while (i < NUM_OF_ITEM_IN_DIET)
	{
		printf("%s", printRecordMenu[i]);
		switch (i)
		{
		case 0:
		{
			printf("ex) 20160102\n");
			fseek(stdin, 0, SEEK_END);
			gets_s(recordDiet->date, sizeof(recordDiet->date));
			//gets(recordDiet->date);
			//checkDate();
			//근데 왜 처음의 gets함수가 무시되고 아래이프문을 실행할까요?
			length = strlen(recordDiet->date);
			//길이를 비교해서 8글자를 입력하게함 나중에 날짜검증하는함수 추가예정.
			if (length == MAX_NUM_OF_DATE)
			{
				i++;
			}
	//		else
	//		{
	//			printf("ex) 20160102\n");
	//		}
			break;
		}
		case 1:
		{
			inputForSelectedMeal = inputforIntOneTofour();

			_itoa(inputForSelectedMeal, recordDiet->selectedMealNum, 10);
			recordDiet->selectedMealNum[1] = '\0';

			if (inputForSelectedMeal == 1)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = breakfast[j];
				}
				i++;
			}
			else if (inputForSelectedMeal == 2)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = lunch[j];
				}
				i++;
			}
			else if (inputForSelectedMeal == 3)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = dinner[j];
				}
				i++;
			}
			else if (inputForSelectedMeal == 4)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = snack[j];
				}
				i++;
			}
			/*
			gets(recordDiet->selectedMeal);
			//checkSelectedMeal();
			length = strlen(recordDiet->selectedMeal);
			if (length == MAX_NUM_OF_SELECTED_MEAL)
			{
				i++;
			}
			else
			{
				printf("아침,점심,저녁,간식중에서 입력해 주세요\n");
			}
			*/
			break;
		}
		case 2:
		{
			fseek(stdin, 0, SEEK_END);
			gets(recordDiet->meal);
			//checkMeal()
			length = strlen(recordDiet->meal);
			//데이터를 읽어올때 탭,개행,스페이스를 구별못해서 임시 방편으로 언더바를 스페이스로 쓰게함. 검색하다보니 %[^\t] 같은 것이 나오는데 정확한 사용법을
			//몰라서 다음숙제기한때 적용해볼예정임.
			if (length <= MAX_NUM_OF_MEAL)
			{
				i++;
			}
			else
			{
				i++;
				printf("%d 글자 까지만 입력됩니다\n", MAX_NUM_OF_MEAL / 2);
				recordDiet->review[MAX_NUM_OF_MEAL] = NULL;
			}
			break;
		}
		case 3:
		{
			gets(recordDiet->review);
			//checkReview()
			length = strlen(recordDiet->review);
			if (length <= MAX_NUM_OF_REVIEW)
			{
				i++;
			}
			else
			{
				i++;
				printf("%d 글자 까지만 입력됩니다\n", MAX_NUM_OF_REVIEW / 2);
				recordDiet->review[MAX_NUM_OF_REVIEW] = NULL;

			}
			break;
		}

		default:
			break;
		}
	}

	insertNewDietToList(listOfDietOnmemory, recordDiet);
}
//식단을 수정하는 함수
int reviseNewDataFromUser(DietL* prevNode, int keyNum)
{
	int i = 0;
	int j;
	int length = 0;
	int inputForSelectedMeal;
	char breakfast[MAX_NUM_OF_SELECTED_MEAL + 1] = "아침";
	char lunch[MAX_NUM_OF_SELECTED_MEAL + 1] = "점심";
	char dinner[MAX_NUM_OF_SELECTED_MEAL + 1] = "저녁";
	char snack[MAX_NUM_OF_SELECTED_MEAL + 1] = "간식";

	DietL* recordDiet = (DietL*)malloc(sizeof(DietL));
	if (recordDiet == NULL)
	{
		return -1;
	}

	while (i < NUM_OF_ITEM_IN_DIET)
	{
		printf("%s", printRecordMenu[i]);
		switch (i)
		{
		case 0:
		{
			printf("ex) 20160102\n");
			fseek(stdin, 0, SEEK_END);
			gets_s(recordDiet->date, sizeof(recordDiet->date));
			//gets(recordDiet->date);
			//checkDate();
			//근데 왜 처음의 gets함수가 무시되고 아래이프문을 실행할까요?
			length = strlen(recordDiet->date);
			//길이를 비교해서 8글자를 입력하게함 나중에 날짜검증하는함수 추가예정.
			if (length == MAX_NUM_OF_DATE)
			{
				i++;
			}
//			else
//			{
//				printf("ex) 20160102\n");
//			}
			break;
		}
		case 1:
		{
			inputForSelectedMeal = inputforIntOneTofour();

			_itoa(inputForSelectedMeal, recordDiet->selectedMealNum, 10);
			recordDiet->selectedMealNum[1] = '\0';

			if (inputForSelectedMeal == 1)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = breakfast[j];
				}
				i++;
			}
			else if (inputForSelectedMeal == 2)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = lunch[j];
				}
				i++;
			}
			else if (inputForSelectedMeal == 3)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = dinner[j];
				}
				i++;
			}
			else if (inputForSelectedMeal == 4)
			{
				for (j = 0; j < (MAX_NUM_OF_SELECTED_MEAL + 1); j++)
				{
					recordDiet->selectedMeal[j] = snack[j];
				}
				i++;
			}
			/*
			gets(recordDiet->selectedMeal);
			//checkSelectedMeal();
			length = strlen(recordDiet->selectedMeal);
			if (length == MAX_NUM_OF_SELECTED_MEAL)
			{
			i++;
			}
			else
			{
			printf("아침,점심,저녁,간식중에서 입력해 주세요\n");
			}
			*/
			break;
		}
		case 2:
		{
			fseek(stdin, 0, SEEK_END);
			gets(recordDiet->meal);
			//checkMeal()
			length = strlen(recordDiet->meal);
			//데이터를 읽어올때 탭,개행,스페이스를 구별못해서 임시 방편으로 언더바를 스페이스로 쓰게함. 검색하다보니 %[^\t] 같은 것이 나오는데 정확한 사용법을
			//몰라서 다음숙제기한때 적용해볼예정임.
			if (length <= MAX_NUM_OF_MEAL)
			{
				i++;
			}
			else
			{
				i++;
				printf("%d 글자 까지만 입력됩니다\n", MAX_NUM_OF_MEAL / 2);
				recordDiet->review[MAX_NUM_OF_MEAL] = NULL;
			}
			break;
		}
		case 3:
		{
			gets(recordDiet->review);
			//checkReview()
			length = strlen(recordDiet->review);
			if (length <= MAX_NUM_OF_REVIEW)
			{
				i++;
			}
			else
			{
				i++;
				printf("%d 글자 까지만 입력됩니다\n", MAX_NUM_OF_REVIEW / 2);
				recordDiet->review[MAX_NUM_OF_REVIEW] = NULL;

			}
			break;
		}

		default:
			break;
		}
	}

	if (keyNum == 1)
	{
		recordDiet->next = listOfDietOnmemory->head;
		listOfDietOnmemory->head = recordDiet;
		listOfDietOnmemory->numOfNode++;
	}
	else
	{
		recordDiet->next = prevNode->next;
		prevNode->next = recordDiet;
		listOfDietOnmemory->numOfNode++;
	}
}
//링크드 리스트에 노드를 넣는 함수
int insertNewDietToList(List* listOfDietOnmemory, DietL* newDiet)
{
	if (listOfDietOnmemory == NULL || newDiet == NULL)
	{
		return -1;
	}
	if (listOfDietOnmemory->head != NULL)
	{
		newDiet->next = listOfDietOnmemory->head;
		listOfDietOnmemory->head = newDiet;
		listOfDietOnmemory->numOfNode++;
	}
	else
	{
		listOfDietOnmemory->head = newDiet;
		listOfDietOnmemory->numOfNode++;
	}
}
//데이터 파일을 읽어 오는 함수
int readDataFromFile()
{
	FILE* fp;
	char str[512];
	char end = '0';
	/*
	char date[MAX_NUM_OF_DATE + 1]; //날짜
	char BrLuDiSn[MAX_NUM_OF_SELECTED_MEAL + 1]; //아침,점심,저녁,간식
	char meal[MAX_NUM_OF_MEAL + 1]; //먹은것
	char review[MAX_NUM_OF_REVIEW + 1]; //반성
	*/
	DietL* tempDiet;
	DietL* newDiet;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("file open failed!!");
		return -1;
	}

	while (1)
	{
		//한줄씩 읽어들이면서 빈줄인지 확인.
		end = fgets(str, sizeof(str), fp);

		//마지막 줄이 null이면 빠져 나온다.
		if (end == NULL)
		{
			return;
		}

		//임시 구조체 할당.
		tempDiet = (DietL*)malloc(sizeof(DietL));
		if (tempDiet == NULL)
		{
			printf("메모리 할당 실패");
			return -1;
		}
		//각각의 행을 delimiter 로 구분해서 나눠서 임시 구조체에 넣어줌.
		cutStr(str, tempDiet);
		//아래 주석처리된 내용을 넣으니 newDiet를 2번째부터 할당을 받지 못함.
		//newDiet = (DietL*)malloc(sizeof(DietL));
		//memcpy(newDiet->date, tempDiet->date, strlen(newDiet->date));
		//memcpy(newDiet->meal, tempDiet->meal, strlen(newDiet->date));
		//memcpy(newDiet->selectedMeal, tempDiet->selectedMeal, strlen(newDiet->date));
		//memcpy(newDiet->review, tempDiet->review, strlen(newDiet->date));
		//free(tempDiet);
		tempDiet->next = NULL;
		insertNewDietToList(listOfDietOnmemory, tempDiet);

	}


}
//데이터 전체를 출력하는 함수
int printdata(List* listOfDietOnmemory)
{
	DietL* curNode;
	curNode = listOfDietOnmemory->head;

	while (curNode != NULL)
	{
		puts(curNode->date);
		puts(curNode->selectedMeal);
		puts(curNode->meal);
		puts(curNode->review);
		//puts(curNode->selectedMealNum);
		printf("\n");
		curNode = curNode->next;
	}
	printf("%d개의 식단일기 존재\n", listOfDietOnmemory->numOfNode);
}
/*
void clearInputBuffer()
{
	while (getchar() != '\n' || getchar() != -1);
}
*/

int printDataBy5(List* listOfDietOnmemory)
{
	DietL* curNode;
	int i=0;
	int page=0;
	int maxPage = listOfDietOnmemory->numOfNode / 5;
	curNode = listOfDietOnmemory->head;
	while (curNode != NULL)
	{
		i++;
		puts(curNode->date);
		puts(curNode->selectedMeal);
		puts(curNode->meal);
		puts(curNode->review);
		//puts(curNode->selectedMealNum);
		printf("\n");
		curNode = curNode->next;
		if (i % 5 == 0)
		{
			printf("앞으로 가고 싶으면 2를 입력해 주세요");
			while (page != 2)
			{
				fseek(stdin, 0, SEEK_END);
				scanf("%d", &page);
				fseek(stdin, 0, SEEK_END);
			}
			system("cls");
			page = 0;
			/*
			if (i > 5 && i < maxPage * 5)
			{
				printf("앞으로 가고 싶으면 2 뒤로 가고 싶으면 1을 눌러 주세요.");
				while (page != 1 || page != 2)
				{
					fseek(stdin, 0, SEEK_END);
					scanf("%d", &page);
					fseek(stdin, 0, SEEK_END);
				}
				if (page == 1)
				{

				}
			}
			*/
		}
	}
}
int inputForMenu()
{
	int input;

	while (scanf_s("%d", &input) != 1)
	{
		fseek(stdin, 0, SEEK_END);
		//clearInputBuffer();
		system("cls");
		printf("1.식단일기 전체보기 2.식단등록 3.식단삭제(구현중) 4.식단수정(구현중) 5.종료하기(구현중)\n");
		printf("잘못된 입력입니다. 원하는 항목의 번호를 입력해 주세요.\n");
	}
	return input;
}

int inputforIntOneTofour()
{
	/*
	int input;
	char charinput;
	do
	{
		charinput = getchar();
		fseek(stdin, 0, SEEK_END);
		if()

	}
	*/
	int input;
	int err = 0;
	do
	{

		err = scanf("%d", &input);

		if (input < 1 && input >4)
		{
			getchar();
			system("cls");
			printf("잘못된 입력입니다. 원하는 항목의 번호를 입력해 주세요.");
			printf("[1.아침 2.점심 3.저녁 4.간식]중에 어떤 것이었나요?\n");
			err = 0;
		}
		//clearInputBuffer();

	} while (err != 1);

	return input;

}

int searchDietByDate(List* listOfDietOnmemory,DietL**searchedNode, char*keyDate)
{
	int isSame;
	int i;
	int indexForSelectDiet = 0;
	DietL* curNode;
	//DietL* prevNode;

	curNode = listOfDietOnmemory->head;
	//prevNode = listOfDietOnmemory->head;

	for (i = 0; i < (listOfDietOnmemory->numOfNode); i++)
	{
		
		isSame = strcmp(curNode->date, keyDate);
		if (isSame == 0)
		{
			//savedNode[(indexForSelectDiet) * 2] = prevNode;
			//savedNode[((indexForSelectDiet) * 2 + 1)] = curNode;
			searchedNode[indexForSelectDiet] = curNode;
			indexForSelectDiet++;
			printf("%d 번\n", indexForSelectDiet);
			puts(curNode->date);
			puts(curNode->selectedMeal);
			puts(curNode->meal);
			puts(curNode->review);
			puts(curNode->selectedMealNum);
			printf("\n");
		}
		//prevNode = curNode;
		curNode = curNode->next;
	}

	if (indexForSelectDiet == 0)
	{
		printf("검색결과 없음!!\n");
	}

	return indexForSelectDiet;

}

int delNode(List* listOfDietOnmemory, DietL**searchedNode,int keyNum)
{
	int isSame = 0;
	int i;
	int indexForSelectDiet = 0;
	DietL* curNode;
	DietL* prevNode;

	curNode = searchedNode[keyNum-1];
	prevNode = listOfDietOnmemory->head;
	if ((keyNum - 1) == 0)
	{
		listOfDietOnmemory->head = listOfDietOnmemory->head->next;
	}
	else
	{
		while (isSame == 0)
		{
			if (prevNode->next == curNode)
			{
				break;
			}
			prevNode = prevNode->next;
		}

		prevNode->next = curNode->next;
		curNode->next = NULL;
		listOfDietOnmemory->numOfNode--;
	}
	

	free(curNode);

	return 0;
}

int reviseNode(List* listOfDietOnmemory, DietL**searchedNode, int keyNum)
{
	int isSame = 0;
	int i;
	int indexForSelectDiet = 0;
	DietL* curNode;
	DietL* prevNode;
	DietL* prevNodeForRevise;

	curNode = searchedNode[keyNum - 1];
	prevNode = listOfDietOnmemory->head;
	prevNodeForRevise = listOfDietOnmemory->head;
	if ((keyNum - 1) == 0)
	{
		listOfDietOnmemory->head = listOfDietOnmemory->head->next;
	}
	else
	{
		while (isSame == 0)
		{
			if (prevNode->next == curNode)
			{
				break;
			}
			prevNode = prevNode->next;
			prevNodeForRevise = prevNodeForRevise->next;
		}

		prevNode->next = curNode->next;
		curNode->next = NULL;
		listOfDietOnmemory->numOfNode--;
	}
	free(curNode);

	reviseNewDataFromUser(prevNodeForRevise,keyNum);

	return 0;
}

void preface()
{
	int end = 0;
	int input;
	int errForDel;
	int numOfSearchedNode;
	int keyNum;
	char keyDate[MAX_NUM_OF_DATE + 1];
	char keyChar;
	int length = 0;
	DietL** searchedNode[20] = {NULL};

	while (end == 0)
	{
		printf("1.식단일기 전체보기\n2.식단등록\n3.식단 검색하기\n4.식단삭제\n5.식단수정\n6.저장 및 종료하기\n");
		input = inputForMenu();
		switch (input)
		{
		case 1:
		{
			system("cls");//system(~~)창크기
			//printdata(listOfDietOnmemory);
			printDataBy5(listOfDietOnmemory);
			break;
		}
		case 2:
		{
			system("cls");
			getNewDataFromUser();
			break;
		}
		case 3:
		{

			while (1)
			{
				printf("검색하고 싶은 식단의 %s", printRecordMenu[0]);
				printf("ex) 20160102\n");
				fseek(stdin, 0, SEEK_END);
				gets_s(keyDate, sizeof(keyDate));

				length = strlen(keyDate);

				if (length == MAX_NUM_OF_DATE)
				{
					searchDietByDate(listOfDietOnmemory,searchedNode, keyDate);
					break;
				}
				
//				else
//				{
//					printf("ex) 20160102\n");
//				}
			}
			break;
		}
		case 4:
		{
			while (1)
			{
				printf("삭제하고 싶은 식단의 %s", printRecordMenu[0]);
				printf("ex) 20160102\n");
				fseek(stdin, 0, SEEK_END);
				gets_s(keyDate, sizeof(keyDate));

				length = strlen(keyDate);

				if (length == MAX_NUM_OF_DATE)
				{
					numOfSearchedNode = searchDietByDate(listOfDietOnmemory , searchedNode, keyDate);
					if (numOfSearchedNode != 0)
					{
						break;
					}
					
				}
//				else
//				{
//					printf("ex) 20160102\n");
//				}
			}
		

			printf("삭제 하고 싶은 식단의 번호를 입력해 주세요.");

			fseek(stdin, 0, SEEK_END);

			keyChar = getchar();

			fseek(stdin, 0, SEEK_END);

			keyNum = (keyChar - 48);

			if (searchedNode[keyNum] == NULL)
			{
				printf("존재 하지 않는 식단입니다.1~%d 사이의 번호를 입력해 주세요.", numOfSearchedNode);
				errForDel = -1;
			}

			delNode(listOfDietOnmemory, searchedNode, keyNum);
			break;
		}
		case 5:
		{
			while (1)
			{
				printf("수정하고 싶은 식단의 %s", printRecordMenu[0]);
				printf("ex) 20160102\n");
				fseek(stdin, 0, SEEK_END);
				gets_s(keyDate, sizeof(keyDate));

				length = strlen(keyDate);

				if (length == MAX_NUM_OF_DATE)
				{
					numOfSearchedNode = searchDietByDate(listOfDietOnmemory, searchedNode, keyDate);
					if (numOfSearchedNode != 0)
					{
						break;
					}

				}
//				else
//				{
//					printf("ex) 20160102\n");
//				}
			}


			printf("수정 하고 싶은 식단의 번호를 입력해 주세요.");

			fseek(stdin, 0, SEEK_END);

			keyChar = getchar();

			fseek(stdin, 0, SEEK_END);

			keyNum = (keyChar - 48);

			if (searchedNode[keyNum] == NULL)
			{
				printf("존재 하지 않는 식단입니다.1~%d 사이의 번호를 입력해 주세요.", numOfSearchedNode);
				errForDel = -1;
			}

			reviseNode(listOfDietOnmemory, searchedNode, keyNum);

			break;
		}
		case 6:
		{
			writeDataToFile();
			end = 1;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}
freeLinkedList(List* list)
{
	DietL* cur = list->head;
	DietL* nextNode = list->head->next;
	while (nextNode != NULL)
	{
		free(cur);
		cur = nextNode;
		nextNode = nextNode->next;
	}
	free(cur);
}
int main(void)
{
	listOfDietOnmemory = (List*)malloc(sizeof(listOfDietOnmemory));
	listOfDietOnmemory->head = NULL;
	listOfDietOnmemory->numOfNode = 0;
	readDataFromFile();
	//writeDataToFile();
	preface();

	freeLinkedList(listOfDietOnmemory);

}