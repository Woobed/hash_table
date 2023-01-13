#define _CRT_SECURE_NO_WARNINGS
#define M 7
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct hasht {
	char key[10]; /*name*/
	float time[8]; /*время*/
	int emp;	/*индикатор заполненности*/
}hasht;


int hf(char name[10]);					/*Хеш-функция*/
int findlast(hasht* table, int index);	/*Поиск последнего заполненного элемента массива*/



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
		puts("Выберете команду\n\nВывести полную хеш-таблицу -> 1\nВывести заполненную часть таблицы ->2\nДобавить пару -> 3\nУдалить пару -> 4\nНайти последнее время старта по ключу(имени) -> 5\nЗакончить -> 0\n");
		scanf("%d", &ptr);
		switch (ptr) {
		case 1: {						/*Вывод полной таблицы*/
			if (fullempty == 0) {
				system("cls");
				printf("Таблица пуста\n\n");
				break;
			}
			else {
				for (int i = 0; i < (M * 3); i++) {
					if (table[i].key == "") {
						printf("ключ --		 |   время --\n");
					}
					else {
						printf("ключ %10s |   время ", table[i].key);
						for (int j = 0; j <= findlast(table, i) ;j++) {		/*Вывод до последнего заполненного элемента*/
							printf(" %.2f", table[i].time[j]);
						}
						puts("\n");
					}
				}
				break;
			}
		}
		case 2: {						/*Вывод только заполненной части таблицы*/
			system("cls");
			for (int i = 0; i < (M*3); i++) {
				if (table[i].emp == 1) {
					printf("ключ %10s |   время ", table[i].key);
					for (int j = 0; j <= findlast(table, i); j++) {
						printf(" %.2f", table[i].time[j]);
					}
					puts("\n");
				}
			}
			break;
		}
		case 3: {			/*Добавление пары ключ-значение в таблицу*/
			float temptime;
			int localflag=0;
			int i = 0;
			int j = 0;
			int chek=0;
			printf("Введите имя  ");
			scanf("%s", &name);
			int hash = hf(name);
			if (table[hash].emp == 1) {					/*Решение коллизий методом прямой адресации*/
				while (table[hash].emp == 1) {
					hash++;
				}
			}
			printf("(хеш - %d)\n\n",hash);
			strcpy(table[hash].key, name);
			while (localflag == 0){
				printf("Введите время(x,y). Еще %d\nЧтобы закончить введите 0\n",8-i);
				scanf("%f", &temptime);
				if (temptime == 0 || i == 7) {				/*Контроль переполнения массива*/
					localflag = 1;
					system("cls");
					continue;
				}
				for (int k = 0; k < i; k++) {				/*Отмена записи повторяющихся значений*/
					chek = 0;
					if (table[hash].time[k] == temptime) {
						chek = 1;
						break;
					}
				}
				if (chek == 1) {
					system("cls");
					printf("Повторяющееся значение удалено\n");
					continue;
				}
				if (table[hash].time[i] == -1) {			/*Контроль расположения крайнего значения в массиве*/
					table[hash].time[i + 1] = -1;
					table[hash].time[i] = temptime;
					i++;
				}
				
			}
			fullempty = 1;
			table[hash].emp = 1;
			break;
		}
		case 4: {			/*Удаление пары */
			char name[10];
			puts("Введите ключ (имя) существующей пары\n");
			scanf("%s", &name);
			int hash = hf(name);
			if (strcmp(table[hash].key, name) != 0) {
				while (strcmp(table[hash].key, name) != 0) {
					hash++;
					if (table[hash].emp == 0) {				
						system("cls");
						printf("Пары несуществует\n\n");
						break;
					}
				}
			}
			if (table[hash].emp != 0) {
				strcpy(table[hash].key, empstr);
				table[hash].emp = 0;
				table[hash].time[0] = -1;
				system("cls");
				printf("УСПЕШНО УДАЛЕНО\n\n");
			}
			break;
		}
		case 5: {				/*Поиск последнего записанного времени по ключу*/
			char name[10];
			int lastindex;
			system("cls");
			puts("Введите имя яхты\n");
			scanf("%s", &name);
			int hash = hf(name);
			if (strcmp(table[hash].key, name)!=0) {
				while (strcmp(table[hash].key, name) != 0) {
					hash++;
					 if (table[hash].emp == 0) {
						system("cls");
						printf("Пары несуществует\n\n");
						break;
					}
				}
			}
			if (table[hash].emp != 0) {
				printf("---------------------------------\nПоследнее записанное время - %.2f\n---------------------------------\n", table[hash].time[findlast(table, hash)]);
			}
			break;
		}
		case 0: {
			flag = 1;
			break;
		}
		default:{
				puts("Команды не существует\n");
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