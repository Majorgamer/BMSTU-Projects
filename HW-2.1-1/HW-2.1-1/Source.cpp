#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "List.h"

int main() {
	setlocale(LC_ALL, "rus");
	List * list;
	List * list_copy;
	List * converted_list;
	List * el;
	data data[2];
	data[0] = 1;
	data[1] = 2;

	list = createList(data, 2); // �������� ������
	addLast(&list, 4); // �������� � ����� ������
	addLast(&list, 5); // �������� � ����� ������
	add(&list, 3, 2); // �������� � ������������ �����
	remove(&list, 3); // �������� ��������
	list_copy = copy(list); // ���������� ������
	converted_list = convert(list); // ����������� ������
	removeList(&list); // ������� ������
	list = join(list_copy, converted_list); // ��������� ��� ������
	
	el = find(list, 5); // ����� �������
	if (el != NULL)
		printf_s("5 is found\n");
	else
		printf_s("5 not found\n");

	el = find(list, 4); // ����� �������
	if (el != NULL)
		printf_s("4 is found\n");
	else
		printf_s("4 not found\n");

	printf_s("Count: %d\n", count(list)); // ���-�� ���������
	save(list, "list.txt"); // ���������
	removeList(&list_copy);
	list_copy = open("list.txt"); // �������
	printf_s("Count: %d\n", count(list_copy)); // ���-�� ���������	

	system("pause");
	return 0;
}