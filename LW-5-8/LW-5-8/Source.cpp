#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int min(int ** mat, int n, int m) {
	int min = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] < min) min = mat[i][j];
		}
	}
	return min;
}

void freeMat(int *** mat, int n) {
	if (*mat == NULL) return; // ���� ������ ��� ������ ���������� ��������

	for (int i = 0; i < n; i++) {
		if ((*mat)[i] != NULL) free((*mat)[i]); // ���� ������ ��� ������ ����� ��������
	}
	free(*mat);
	*mat = NULL;
}

bool initMat(int *** mat, int n, int m) {
	*mat = (int **)malloc(sizeof(int *) * n);
	if (*mat == NULL) return false;
	for (int i = 0; i < n; i++) {
		(*mat)[i] = (int *)malloc(sizeof(int) * m);
		if ((*mat)[i] == NULL) {
			freeMat(mat, n);
			return false;
		}
		for (int j = 0; j < m; j++) {
			(*mat)[i][j] = rand() % 10;
		}
	}
	return true;
}

void printMat(int ** mat, int n, int m) {
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			printf_s("%d ", mat[i][j]);
		}
		printf_s("\n");
	}
}

int main() {
	setlocale(LC_ALL, "rus");

	int n1 = 0, m1 = 0;
	printf_s("������� n1 � m1: ");
	scanf_s("%d%d", &n1, &m1);

	int ** mat1;
	if (!initMat(&mat1, n1, m1)) {
		printf_s("���������� �������� ������!\n");
		system("pause");
	}	

	int n2 = 0, m2 = 0;
	printf_s("������� n2 � m2: ");
	scanf_s("%d%d", &n2, &m2);
	
	int ** mat2;
	if (!initMat(&mat2, n2, m2)) {
		freeMat(&mat1, n1);
		printf_s("���������� �������� ������!\n");
		system("pause");
	}

	int n3 = 0;
	int m3 = 0;
	printf_s("������� n3 � m3: ");
	scanf_s("%d%d", &n3, &m3);
	
	int ** mat3;
	if (!initMat(&mat3, n3, m3)) {
		freeMat(&mat1, n1);
		freeMat(&mat2, n2);
		printf_s("���������� �������� ������!\n");
		system("pause");
	}

	printf_s("\n������ �������:\n");
	printMat(mat1, n1, m1);
	
	printf_s("\n������ �������:\n");
	printMat(mat2, n2, m2);
	
	printf_s("\n������ �������:\n");
	printMat(mat3, n3, m3);

	int sum = min(mat1, n1, m1) + min(mat2, n2, m2) + min(mat3, n3, m3);
	printf_s("\n����� ����������� ���������: %d\n", sum);

	system("pause");
	return 0;
}