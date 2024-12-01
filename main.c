#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int menu_count = 0; //메뉴 번호 인덱스
int snack_count = 0;
int order_count = 0; //주문 개수 체크 


typedef struct
{
	char name[50];
	int price;
	int count; //재고량

}DrinkList;
typedef struct
{
	char name[50];
	int price;
	int count; //재고량

}SnackList;
DrinkList** drink_menu = NULL;
SnackList** snack_menu = NULL;

//사용자 주문 내역을 저장할 구조체
typedef struct
{
	char name[20];
	int price;
}customerOrder;

customerOrder** order_list = NULL;




void reset_drink_menu()
{
	FILE* drink_fp = fopen("drink2.txt", "r");
	if (drink_fp == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	char line[100];
	int index; //데이터 위치 표시



	while (fgets(line, sizeof(line), drink_fp) != NULL)
	{
		drink_menu = (DrinkList**)realloc(drink_menu, (menu_count + 1) * sizeof(DrinkList*));

		if (drink_menu == NULL)
		{
			printf("메모리 할당 실패\n");
			fclose(drink_fp);
			return;
		}
		DrinkList* imsi_drink = (DrinkList*)malloc(sizeof(DrinkList));
		sscanf(line, "%s %d %d", imsi_drink->name, &imsi_drink->price, &imsi_drink->count);
		//ssanf(line, "%d %d", &imsi_drink->price, &imsi_drink->count);
		drink_menu[menu_count] = imsi_drink;

		menu_count++;

	}
	fclose(drink_fp);
}

void reset_snack_menu()
{
	FILE* snack_fp = fopen("snack2.txt", "r");
	if (snack_fp == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return;
	}

	char line[100];


	while (fgets(line, sizeof(line), snack_fp) != NULL)
	{
		snack_menu = (SnackList**)realloc(snack_menu, (snack_count + 1) * sizeof(SnackList*));

		if (drink_menu == NULL)
		{
			printf("메모리 할당 실패\n");
			fclose(snack_fp);
			return;
		}
		SnackList* imsi_snack = (SnackList*)malloc(sizeof(SnackList));
		sscanf(line, "%s %d %d", imsi_snack->name, &imsi_snack->price, &imsi_snack->count);
		//ssanf(line, "%d %d", &imsi_drink->price, &imsi_drink->count);
		snack_menu[snack_count] = imsi_snack;

		snack_count++;

	}
	fclose(snack_fp);
}

//메뉴 출력, 주문 받기
void service_mode(DrinkList** drink_menu, SnackList** snack_menu)
{
	//drink 메뉴 출력
	printf("===========drink Menu ============\n");
	for (int i = 0; i < menu_count; i++)
	{
		printf("%d : %s\t%d\t%d\n", i + 1, drink_menu[i]->name, drink_menu[i]->price, drink_menu[i]->count);
	}

	//snack메뉴 출력
	printf("========= snack Menu ============\n");
	for (int i = 0; i < snack_count; i++)
	{
		printf("%d : %s\t%d\t%d\n", i + 1, snack_menu[i]->name, snack_menu[i]->price, snack_menu[i]->count);
	}

	int type; //1~3
	FILE* receipt_fp = fopen("receipt.txt", "w");  //영수증 텍스트 파일 쓰기모드로 열기

	while (1)
	{
		printf("Type 1 for drink, 2 for snack, 3 for buy : ");
		scanf("%d", &type);

		if (type == 1) //drink 메뉴 주문
		{
			printf("Type drink id to buy : ");
			scanf("%d", &type);
			//배열의 인덱스 -1 에 위치한 메뉴명과 가격을 저장
			if (type <= menu_count)
			{
				if (drink_menu[type - 1]->count != 0)
				{
					order_list = (customerOrder**)realloc(order_list, (order_count + 1) * sizeof(customerOrder*));
					fputs(drink_menu[type - 1], receipt_fp);
					drink_menu[type - 1]->count--; //1감소
					order_count++;
				}
				else //재고 0인 경우 : 주문 불가 메세지 출력
				{
					printf("Out of stock!");
				}
			}
			else
			{
				printf("It isn't exist on list .");
			}



		}
		else if (type == 2) //snack 메뉴 주문
		{
			printf("Type snack id to buy : ");
			scanf("%d", &type);
			if (type <= snack_count)
			{
				if (snack_menu[type - 1]->count != 0)
				{
					order_list = (customerOrder**)realloc(order_list, (order_count + 1) * sizeof(customerOrder*));
					fputs(snack_menu[type - 1], receipt_fp);
					snack_menu[type - 1]->count--; //1감소
					order_count++;
				}
				else
				{
					printf("Out of stock!");
					continue;
				}
			}
			else
			{
				printf("It isn't exist on list .");
			}

		}
		else if (type == 3)
		{
			break;
		}
	}



}

char print_receipt() //영수증 발급
{

	int total = 0;
	for (int i = 0; i < order_count; i++)
	{
		//total+=receipt
	}
	printf("=======Receipt=========\n");
	/*
	* 이곳에 주문 메뉴 이름과 가격이 한줄씩 출력되게 해야함
	*/
	printf("=======================");
}
//admin or user
int check_ID(char* input[], int* id_index)
{
	int p = &id_index;

	while (1)
	{

		printf("Mode Select (admin or user) :");
		scanf("%s", input);

		if (strcmp(input, "admin") == 0)
		{
			p = 1;
			break;
		}
		else if (strcmp(input, "user") == 0)
		{
			break;
		}
		else
		{
			printf("Error : Wrong Input!\n\n");
		}
	}

}

int main(void)
{
	char* input[10]; //포인터로 선언
	int* id_index = 0;
	check_ID(input, id_index);
	//0: user mode , 1: admin mode 
	//제대로 입력할 때까지 계속 id를 입력받으니까 이외의 경우는 둘 필요가 없음

	if (id_index == 1)//admin mode
	{
		printf("admin mode\n\n");
	}
	else
	{
		printf("user mode\n\n");
		reset_drink_menu();
		reset_snack_menu();
		service_mode(drink_menu, snack_menu);
	}


	//메모리 해제
	for (int i = 0; i < menu_count; i++)
	{
		free(drink_menu[i]);

	}
	free(drink_menu);

	for (int i = 0; i < snack_count; i++)
	{
		free(snack_menu[i]);
	}
	free(snack_menu);


}