#pragma once

typedef int data;

struct List {
	data data;
	List * next;
};

List * createList(data * data, int data_number); // �������� ������
int addLast(List ** list, data data); // �������� � ����� ������
int add(List ** list, data data, int number); // �������� � ������������ �����
void remove(List ** list, int number); // �������� ��������
List * join(List * a, List * b); // ��������� ��� ������
List * convert(List * list); // ����������� ������
void removeList(List ** list); // ������� ������
List * copy(List * list); // ���������� ������
List * find(List * list, data data); // ����� �������
int count(List * list); // ���-�� ���������
void save(List * list, char * filename); // ���������
List * open(char * filename); // �������