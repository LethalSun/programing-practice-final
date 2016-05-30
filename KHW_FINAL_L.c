#include "Header.h"

List* listOfDietOnmemory;

// data.txt�� �����ϴ� �Լ�.
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

//���������Ͽ��� ���پ� �о�� �����͸� delimeter�� �߶� ����ü�� �ִ� �Լ�
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
					//�̺κ� ���� �ʿ� ��ħ���� ��.
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
			//��ħ ���� ���� ������ �����ϱ� ���� ��ȣ
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
//�Ĵ��� �Է� �޴� �Լ�.
int getNewDataFromUser()
{
	int i = 0;
	int j;
	int length = 0;
	int inputForSelectedMeal;
	char breakfast[MAX_NUM_OF_SELECTED_MEAL + 1] = "��ħ";
	char lunch[MAX_NUM_OF_SELECTED_MEAL + 1] = "����";
	char dinner[MAX_NUM_OF_SELECTED_MEAL + 1] = "����";
	char snack[MAX_NUM_OF_SELECTED_MEAL + 1] = "����";

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
			//�ٵ� �� ó���� gets�Լ��� ���õǰ� �Ʒ��������� �����ұ��?
			length = strlen(recordDiet->date);
			//���̸� ���ؼ� 8���ڸ� �Է��ϰ��� ���߿� ��¥�����ϴ��Լ� �߰�����.
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
				printf("��ħ,����,����,�����߿��� �Է��� �ּ���\n");
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
			//�����͸� �о�ö� ��,����,�����̽��� �������ؼ� �ӽ� �������� ����ٸ� �����̽��� ������. �˻��ϴٺ��� %[^\t] ���� ���� �����µ� ��Ȯ�� ������
			//���� �����������Ѷ� �����غ�������.
			if (length <= MAX_NUM_OF_MEAL)
			{
				i++;
			}
			else
			{
				i++;
				printf("%d ���� ������ �Էµ˴ϴ�\n", MAX_NUM_OF_MEAL / 2);
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
				printf("%d ���� ������ �Էµ˴ϴ�\n", MAX_NUM_OF_REVIEW / 2);
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
//�Ĵ��� �����ϴ� �Լ�
int reviseNewDataFromUser(DietL* prevNode, int keyNum)
{
	int i = 0;
	int j;
	int length = 0;
	int inputForSelectedMeal;
	char breakfast[MAX_NUM_OF_SELECTED_MEAL + 1] = "��ħ";
	char lunch[MAX_NUM_OF_SELECTED_MEAL + 1] = "����";
	char dinner[MAX_NUM_OF_SELECTED_MEAL + 1] = "����";
	char snack[MAX_NUM_OF_SELECTED_MEAL + 1] = "����";

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
			//�ٵ� �� ó���� gets�Լ��� ���õǰ� �Ʒ��������� �����ұ��?
			length = strlen(recordDiet->date);
			//���̸� ���ؼ� 8���ڸ� �Է��ϰ��� ���߿� ��¥�����ϴ��Լ� �߰�����.
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
			printf("��ħ,����,����,�����߿��� �Է��� �ּ���\n");
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
			//�����͸� �о�ö� ��,����,�����̽��� �������ؼ� �ӽ� �������� ����ٸ� �����̽��� ������. �˻��ϴٺ��� %[^\t] ���� ���� �����µ� ��Ȯ�� ������
			//���� �����������Ѷ� �����غ�������.
			if (length <= MAX_NUM_OF_MEAL)
			{
				i++;
			}
			else
			{
				i++;
				printf("%d ���� ������ �Էµ˴ϴ�\n", MAX_NUM_OF_MEAL / 2);
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
				printf("%d ���� ������ �Էµ˴ϴ�\n", MAX_NUM_OF_REVIEW / 2);
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
//��ũ�� ����Ʈ�� ��带 �ִ� �Լ�
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
//������ ������ �о� ���� �Լ�
int readDataFromFile()
{
	FILE* fp;
	char str[512];
	char end = '0';
	/*
	char date[MAX_NUM_OF_DATE + 1]; //��¥
	char BrLuDiSn[MAX_NUM_OF_SELECTED_MEAL + 1]; //��ħ,����,����,����
	char meal[MAX_NUM_OF_MEAL + 1]; //������
	char review[MAX_NUM_OF_REVIEW + 1]; //�ݼ�
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
		//���پ� �о���̸鼭 �������� Ȯ��.
		end = fgets(str, sizeof(str), fp);

		//������ ���� null�̸� ���� ���´�.
		if (end == NULL)
		{
			return;
		}

		//�ӽ� ����ü �Ҵ�.
		tempDiet = (DietL*)malloc(sizeof(DietL));
		if (tempDiet == NULL)
		{
			printf("�޸� �Ҵ� ����");
			return -1;
		}
		//������ ���� delimiter �� �����ؼ� ������ �ӽ� ����ü�� �־���.
		cutStr(str, tempDiet);
		//�Ʒ� �ּ�ó���� ������ ������ newDiet�� 2��°���� �Ҵ��� ���� ����.
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
//������ ��ü�� ����ϴ� �Լ�
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
	printf("%d���� �Ĵ��ϱ� ����\n", listOfDietOnmemory->numOfNode);
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
			printf("������ ���� ������ 2�� �Է��� �ּ���");
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
				printf("������ ���� ������ 2 �ڷ� ���� ������ 1�� ���� �ּ���.");
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
		printf("1.�Ĵ��ϱ� ��ü���� 2.�Ĵܵ�� 3.�Ĵܻ���(������) 4.�Ĵܼ���(������) 5.�����ϱ�(������)\n");
		printf("�߸��� �Է��Դϴ�. ���ϴ� �׸��� ��ȣ�� �Է��� �ּ���.\n");
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
			printf("�߸��� �Է��Դϴ�. ���ϴ� �׸��� ��ȣ�� �Է��� �ּ���.");
			printf("[1.��ħ 2.���� 3.���� 4.����]�߿� � ���̾�����?\n");
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
			printf("%d ��\n", indexForSelectDiet);
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
		printf("�˻���� ����!!\n");
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
		printf("1.�Ĵ��ϱ� ��ü����\n2.�Ĵܵ��\n3.�Ĵ� �˻��ϱ�\n4.�Ĵܻ���\n5.�Ĵܼ���\n6.���� �� �����ϱ�\n");
		input = inputForMenu();
		switch (input)
		{
		case 1:
		{
			system("cls");//system(~~)âũ��
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
				printf("�˻��ϰ� ���� �Ĵ��� %s", printRecordMenu[0]);
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
				printf("�����ϰ� ���� �Ĵ��� %s", printRecordMenu[0]);
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
		

			printf("���� �ϰ� ���� �Ĵ��� ��ȣ�� �Է��� �ּ���.");

			fseek(stdin, 0, SEEK_END);

			keyChar = getchar();

			fseek(stdin, 0, SEEK_END);

			keyNum = (keyChar - 48);

			if (searchedNode[keyNum] == NULL)
			{
				printf("���� ���� �ʴ� �Ĵ��Դϴ�.1~%d ������ ��ȣ�� �Է��� �ּ���.", numOfSearchedNode);
				errForDel = -1;
			}

			delNode(listOfDietOnmemory, searchedNode, keyNum);
			break;
		}
		case 5:
		{
			while (1)
			{
				printf("�����ϰ� ���� �Ĵ��� %s", printRecordMenu[0]);
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


			printf("���� �ϰ� ���� �Ĵ��� ��ȣ�� �Է��� �ּ���.");

			fseek(stdin, 0, SEEK_END);

			keyChar = getchar();

			fseek(stdin, 0, SEEK_END);

			keyNum = (keyChar - 48);

			if (searchedNode[keyNum] == NULL)
			{
				printf("���� ���� �ʴ� �Ĵ��Դϴ�.1~%d ������ ��ȣ�� �Է��� �ּ���.", numOfSearchedNode);
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