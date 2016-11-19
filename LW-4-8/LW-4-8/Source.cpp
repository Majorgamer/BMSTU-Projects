#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

struct disp {
	char name[64];
	int mark;
};
struct student {
	char fio[128];
	disp disps[4];
};


int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	printf_s("������� n: ");
	scanf_s("%d", &n);
	student * s;
	s = (student *)malloc(sizeof(student)*n);
	if (s == NULL) {
		printf_s("���������� �������� ������! ");
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		printf_s("������� ���: ");
		_flushall();
		gets_s(s[i].fio, 127);

		for (int j = 0; j < 4; j++) {
			printf_s("������� �������� ��������: ");
			fflush(stdin);
			gets_s(s[i].disps[j].name, 63);
			printf_s("������� ������ �� �������� \"%s\": ", s[i].disps[j].name);
			scanf_s("%d", &s[i].disps[j].mark);
		}
	}

	double max = -1;
	int k = -1;
	for (int j = 0; j < 4; j++) {
		double avr = 0;
		for (int i = 0; i < n; i++) {
			avr += s[i].disps[j].mark;
		}
		avr /= n;
		if (avr > max) {
			max = avr;
			k = j;
		}
	}

	printf_s("������� \"%s\" ��� ���� ������� ����� �����!\n", s[0].disps[k].name);

	free(s);
	system("pause");
	return 0;
}