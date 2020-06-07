#include "funcktion.h"
#include <string.h>
#include <locale.h>
#include <stdio.h>


int sum(int matrix[][8])
{
	int summa = 0;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			summa += matrix[r][c];
		}
	}
	return summa;
}



void copy(int m1[][8], int m2[][8])
{
	for (int g = 0; g < 8; g++)
	{
		for (int f = 0; f < 8; f++)
		{
			m2[g][f] = m1[g][f];
		}
	}
	return;
}


void clear(int mass[], int size)
{
	for (int g = 0; g < size; g++)
		mass[g] = -1;

	return;
}

void full(int matrix[][8], int a, int b)
{
	if (a == 0 && b == 0)
	{
		matrix[a + 1][b] += 1;
		matrix[a + 1][b + 1] += 1;
		matrix[a][b + 1] += 1;
	}
	else if (a == 7 && b == 0)
	{
		matrix[a - 1][b] += 1;
		matrix[a - 1][b + 1] += 1;
		matrix[a][b + 1] += 1;
	}
	else if (a == 0 && b == 7)
	{
		matrix[a + 1][b] += 1;
		matrix[a + 1][b - 1] += 1;
		matrix[a][b - 1] += 1;
	}
	else if (a == 7 && b == 7)
	{
		matrix[a - 1][b] += 1;
		matrix[a - 1][b - 1] += 1;
		matrix[a][b - 1] += 1;
	}
	else if (a > 0 && b == 0 && a < 7)
	{
		matrix[a - 1][b] += 1;
		matrix[a + 1][b] += 1;
		matrix[a - 1][b + 1] += 1;
		matrix[a + 1][b + 1] += 1;
		matrix[a][b + 1] += 1;
	}
	else if (a == 0 && b > 0 && b < 7)
	{
		matrix[a][b - 1] += 1;
		matrix[a + 1][b - 1] += 1;
		matrix[a + 1][b] += 1;
		matrix[a + 1][b + 1] += 1;
		matrix[a][b + 1] += 1;
	}
	else if (a > 0 && b == 7 && a < 7)
	{
		matrix[a - 1][b] += 1;
		matrix[a - 1][b - 1] += 1;
		matrix[a][b - 1] += 1;
		matrix[a + 1][b - 1] += 1;
		matrix[a + 1][b] += 1;
	}
	else if (a == 7 && b > 0 && b < 7)
	{
		matrix[a][b - 1] += 1;
		matrix[a - 1][b - 1] += 1;
		matrix[a - 1][b] += 1;
		matrix[a - 1][b + 1] += 1;
		matrix[a][b + 1] += 1;
	}
	else
	{
		matrix[a][b - 1] += 1;
		matrix[a - 1][b - 1] += 1;
		matrix[a - 1][b] += 1;
		matrix[a - 1][b + 1] += 1;
		matrix[a][b + 1] += 1;
		matrix[a + 1][b + 1] += 1;
		matrix[a + 1][b] += 1;
		matrix[a + 1][b - 1] += 1;
	}

	return;
}

void matr(int matrix[][8], int kol, int a, int b)
{
	int i = a, j = b, mas_i[64], mas_j[64], mass[8][8];

	clear(mas_i, 64);
	clear(mas_j, 64);

	for (int s = 1; s <= kol; s++)
	{
		if (s == 1)
		{
			full(matrix, i, j);
		}

		else 
		{
			copy(matrix, mass);

			for (int r = 0; r < 8; r++)
			{

				for (int c = 0; c < 8; c++)
				{
					if (mass[r][c] > 0)
					{
						for (int k = 0; k < 64; k++)
						{

							if (mas_i[k] == -1)
							{
								mas_i[k] = r;
								mas_j[k] = c;
								goto lebel1;
							}
						}
					lebel1:
						mass[r][c] = 0;
					}

				}

			}

			for (int k = 0; k < 64; k++)
			{

				if (mas_i[k] != -1)
				{
					full(matrix, mas_i[k], mas_j[k]);
				}
			}
			clear(mas_i, 64);
			clear(mas_j, 64);
		}


	}
	return;
}


void input(char* mass, char* mas2, char* mas1, int* a, int* b, int size)
{
	*b = strcspn(mass, mas1) - 1;
	*a = strcspn(mas2, mas1);
	if (*b >= 8)
		*b -= 8;
	return;
}


void output_matr(int matrix[][8], char* s, char* t, int size_1, int size_2)
{
	for (int r = 0; r < size_1; r++)
	{
		printf("%4c", s[r]);
		for (int c = 0; c < size_1; c++)
		{
			printf("%4i", matrix[r][c]);
		}
		printf("\n\n");
	}
	for (int r = 0; r < size_2; r++)
		printf("%4c", t[r]);
	printf("\n\n");
	return;
}


void menu()
{
	setlocale(LC_CTYPE, "rus");
	int v = 0, g = 0, m = 0,
		doska[8][8] = { 0 };

	char m1[3], * str = " ABCDEFGHabcdefgh", * str1 = "87654321";
	printf("Введите координаты шахматной доски: ");
	fgets(m1, 3, stdin);
	printf("Введите кол-во ходов короля: ");
	scanf_s("%i", &m);
	input(str, str1, m1, &v, &g, 8);
	matr(doska, m, v, g);
	printf("Возможное кол-во ходов: %i\n\n", sum(doska));
	printf("Вывод шахматной доски:\n\n");
	output_matr(doska, str1, str, 8, 9);
	return;
}