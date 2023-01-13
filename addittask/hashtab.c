#define _CRT_SECURE_NO_WARNINGS
#define M 7
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct hasht {
	char key[10]; /*name*/
	float time[8]; /*�����*/
	int emp;	/*��������� �������������*/
}hasht;


int hf(char name[10]);					/*���-�������*/
int findlast(hasht* table, int index);	/*����� ���������� ������������ �������� �������*/



int main() {
	setlocale(LC_ALL, "RUS");
	hasht* table;
	table = calloc((M * 3), sizeof(hasht));
	char name[10];
	char empstr[] = "";
	int flag = 0;
	int ptr;
	int fullempty = 0;
	for (int i = 0; i < (M * 3); i++) {
		table[i].time[0] = -1;

	}
	while (flag == 0) {
		puts("�������� �������\n\n������� ������ ���-������� -> 1\n������� ����������� ����� ������� ->2\n�������� ���� -> 3\n������� ���� -> 4\n����� ��������� ����� ������ �� �����(�����) -> 5\n��������� -> 0\n");
		scanf("%d", &ptr);
		switch (ptr) {
		case 1: {						/*����� ������ �������*/
			if (fullempty == 0) {
				system("cls");
				printf("������� �����\n\n");
				break;
			}
			else {
				for (int i = 0; i < (M * 3); i++) {
					if (table[i].key == "") {
						printf("���� --		 |   ����� --\n");
					}
					else {
						printf("���� %10s |   ����� ", table[i].key);
						for (int j = 0; j <= findlast(table, i) ;j++) {		/*����� �� ���������� ������������ ��������*/
							printf(" %.2f", table[i].time[j]);
						}
						puts("\n");
					}
				}
				break;
			}
		}
		case 2: {						/*����� ������ ����������� ����� �������*/
			system("cls");
			for (int i = 0; i < (M*3); i++) {
				if (table[i].emp == 1) {
					printf("���� %10s |   ����� ", table[i].key);
					for (int j = 0; j <= findlast(table, i); j++) {
						printf(" %.2f", table[i].time[j]);
					}
					puts("\n");
				}
			}
			break;
		}
		case 3: {			/*���������� ���� ����-�������� � �������*/
			float temptime;
			int localflag=0;
			int i = 0;
			int j = 0;
			int chek=0;
			printf("������� ���  ");
			scanf("%s", &name);
			int hash = hf(name);
			if (table[hash].emp == 1) {					/*������� �������� ������� ������ ���������*/
				while (table[hash].emp == 1) {
					hash++;
				}
			}
			printf("(��� - %d)\n\n",hash);
			strcpy(table[hash].key, name);
			while (localflag == 0){
				printf("������� �����(x,y). ��� %d\n����� ��������� ������� 0\n",8-i);
				scanf("%f", &temptime);
				if (temptime == 0 || i == 7) {				/*�������� ������������ �������*/
					localflag = 1;
					system("cls");
					continue;
				}
				for (int k = 0; k < i; k++) {				/*������ ������ ������������� ��������*/
					chek = 0;
					if (table[hash].time[k] == temptime) {
						chek = 1;
						break;
					}
				}
				if (chek == 1) {
					system("cls");
					printf("������������� �������� �������\n");
					continue;
				}
				if (table[hash].time[i] == -1) {			/*�������� ������������ �������� �������� � �������*/
					table[hash].time[i + 1] = -1;
					table[hash].time[i] = temptime;
					i++;
				}
				
			}
			fullempty = 1;
			table[hash].emp = 1;
			break;
		}
		case 4: {			/*�������� ���� */
			char name[10];
			puts("������� ���� (���) ������������ ����\n");
			scanf("%s", &name);
			int hash = hf(name);
			if (strcmp(table[hash].key, name) != 0) {
				while (strcmp(table[hash].key, name) != 0) {
					hash++;
					if (table[hash].emp == 0) {				
						system("cls");
						printf("���� ������������\n\n");
						break;
					}
				}
			}
			if (table[hash].emp != 0) {
				strcpy(table[hash].key, empstr);
				table[hash].emp = 0;
				table[hash].time[0] = -1;
				system("cls");
				printf("������� �������\n\n");
			}
			break;
		}
		case 5: {				/*����� ���������� ����������� ������� �� �����*/
			char name[10];
			int lastindex;
			system("cls");
			puts("������� ��� ����\n");
			scanf("%s", &name);
			int hash = hf(name);
			if (strcmp(table[hash].key, name)!=0) {
				while (strcmp(table[hash].key, name) != 0) {
					hash++;
					 if (table[hash].emp == 0) {
						system("cls");
						printf("���� ������������\n\n");
						break;
					}
				}
			}
			if (table[hash].emp != 0) {
				printf("---------------------------------\n��������� ���������� ����� - %.2f\n---------------------------------\n", table[hash].time[findlast(table, hash)]);
			}
			break;
		}
		case 0: {
			flag = 1;
			break;
		}
		default:{
				puts("������� �� ����������\n");
				break;
			}
		}
	}
}

int hf(char name[10]) {
	unsigned int hashindex=0;
	for (int i = 0; i < strlen(name); i++) {
		hashindex += (unsigned int)name[i];
	}
	hashindex = hashindex % ((M*3)-1);
	return hashindex;
}

int findlast(hasht* table, int index) {
	int j;
	for (j = 0; j < 7; j++) {
		if (table[index].time[j] < 0) {
			break;
		}
	}
	return j - 1;
}