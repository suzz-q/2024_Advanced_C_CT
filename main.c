#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_receipt();

int menu_count = 0; //�޴� ��ȣ �ε���
int snack_count = 0;
int order_count = 0; //�ֹ� ���� üũ 
int receipt = 0; //�̰ɷ� ����ü üũ

typedef struct
{
	char name[50];
	int price;
	int count; //���

}DrinkList;
typedef struct
{
	char name[50];
	int price;
	int count; //���

}SnackList;
DrinkList** drink_menu = NULL;
SnackList** snack_menu = NULL;

//����� �ֹ� ������ ������ ����ü
typedef struct
{
	char name[20];
	int price;
}customerOrder;

customerOrder** order_list;





void reset_drink_menu()
{
	FILE* drink_fp = fopen("drink2.txt", "r");
	if (drink_fp == NULL)
	{
		printf("������ �� �� �����ϴ�.\n");
		return;
	}

	char line[100];
	int index; //������ ��ġ ǥ��



	while (fgets(line, sizeof(line), drink_fp) != NULL)
	{
		drink_menu = (DrinkList**)realloc(drink_menu, (menu_count + 1) * sizeof(DrinkList*));

		if (drink_menu == NULL)
		{
			printf("�޸� �Ҵ� ����\n");
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
		printf("������ �� �� �����ϴ�.\n");
		return;
	}

	char line[100];


	while (fgets(line, sizeof(line), snack_fp) != NULL)
	{
		snack_menu = (SnackList**)realloc(snack_menu, (snack_count + 1) * sizeof(SnackList*));

		if (drink_menu == NULL)
		{
			printf("�޸� �Ҵ� ����\n");
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

//�޴� ���, �ֹ� �ޱ�
void service_mode() {
	printf("===========drink Menu ============\n");
	for (int i = 0; i < menu_count; i++) {
		printf("%d : %s\t%d\t%d\n", i + 1, drink_menu[i]->name, drink_menu[i]->price, drink_menu[i]->count);
	}
	//printf("%d : %s\t\t%d\t\t%d\n", 2, drink_menu[2]->name, drink_menu[2]->price, drink_menu[2]->count);
	printf("========= snack Menu ============\n");
	for (int i = 0; i < snack_count; i++) {
		printf("%d : %s\t%d\t%d\n", i + 1, snack_menu[i]->name, snack_menu[i]->price, snack_menu[i]->count);
	}

	int type; // 1~3
	

	while (1) {
		printf("Type 1 for drink, 2 for snack, 3 for buy : ");
		scanf("%d", &type);

		if (type == 1) { // drink �޴� �ֹ�
			printf("Type drink id to buy : ");
			scanf("%d", &type);

			if (type <= menu_count) {
				if (drink_menu[type - 1]->count != 0) {
					// �ֹ� ����Ʈ Ȯ�� �� �ʱ�ȭ
					order_list = (customerOrder**)realloc(order_list, (order_count + 1) * sizeof(customerOrder*));
					if (order_list == NULL) {
						printf("�޸� ���Ҵ� ����!\n");
						exit(1);
					}
					order_list[order_count] = (customerOrder*)malloc(sizeof(customerOrder));
					if (order_list[order_count] == NULL) {
						printf("�޸� �Ҵ� ����!\n");
						exit(1);
					}

					
					
					strcpy(order_list[order_count]->name, drink_menu[type - 1]->name);
					order_list[order_count]->price = drink_menu[type - 1]->price;

					
					drink_menu[type - 1]->count--; // ��� ����
					order_count++;
				}
				else {
					printf("Out of stock!\n");
				}
			}
			else {
				printf("It isn't exist on the list.\n");
			}

		}
		else if (type == 2) { // snack �޴� �ֹ�
			printf("Type snack id to buy : ");
			scanf("%d", &type);

			if (type <= snack_count) {
				if (snack_menu[type - 1]->count != 0) {
					// �ֹ� ����Ʈ Ȯ�� �� �ʱ�ȭ
					order_list = (customerOrder**)realloc(order_list, (order_count + 1) * sizeof(customerOrder*));
					if (order_list == NULL) {
						printf("�޸� ���Ҵ� ����!\n");
						exit(1);
					}
					order_list[order_count] = (customerOrder*)malloc(sizeof(customerOrder));
					if (order_list[order_count] == NULL) {
						printf("�޸� �Ҵ� ����!\n");
						exit(1);
					}

					

					//�ֹ� ���� ����ü�� �ٿ��ֱ�
					strcpy(order_list[order_count]->name, snack_menu[type - 1]->name);
					order_list[order_count]->price = snack_menu[type - 1]->price;

					

					snack_menu[type - 1]->count--; // ��� ����
					order_count++;
				}
				else {
					printf("Out of stock!\n");
				}
			}
			else {
				printf("It isn't exist on the list.\n");
			}

		}
		else if (type == 3) { // ���� �Ϸ�
			break;
		}
		else {
			printf("Invalid option!\n");
		}
	}

	print_receipt();

	

	// �ֹ� ����Ʈ �޸� ����
	for (int i = 0; i < order_count; i++) {
		free(order_list[i]);
	}
	free(order_list);
}

void print_receipt() //������ �߱�
{
	FILE* receipt_fp = fopen("receipt.txt", "w"); // ������ ���� ����

	if (receipt_fp == NULL) {
		printf("������ ������ �� �� �����ϴ�!\n");
		return;
	}

	int total = 0;
	for (int i = 0; i < order_count; i++)
	{
		total += order_list[i]->price;
	}
	printf("=======Receipt=========\n");
	for (int i = 0; i < order_count; i++)
	{
		fprintf(receipt_fp, "%s\t%d\n", order_list[i]->name, order_list[i]->price);
		printf("%s\t%d\n", order_list[i]->name, order_list[i]->price);
	}
	printf("Total:%d", total);
	fprintf(receipt_fp, "Total : %d", total);
	printf("=======================");
	fclose(receipt_fp);
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
	char* input[10]; //�����ͷ� ����
	int* id_index = 0;
	check_ID(input, id_index);
	//0: user mode , 1: admin mode 
	//����� �Է��� ������ ��� id�� �Է¹����ϱ� �̿��� ���� �� �ʿ䰡 ����

	if (id_index == 1)//admin mode
	{
		printf("admin mode\n\n");
	}
	else
	{
		printf("user mode\n\n");
		reset_drink_menu();
		reset_snack_menu();
		service_mode();
	}


	//�޸� ����
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