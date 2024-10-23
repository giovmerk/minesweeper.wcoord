#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
int find_nbr(char matrix[11][11], int coord, int BCoord[10])
{
	int count = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (coord - 10 + i == BCoord[j])
			{
				count++;
			}
		}
		for (int j = 0; j < 10; j++)
		{
			if (coord + i == BCoord[j])
			{
				count++;
			}
		}
		for (int j = 0; j < 10; j++)
		{
			if (coord + 10 + i == BCoord[j])
			{
				count++;
			}
		}
	}
	return count;
}

void display(char matrix[11][11], int BCoord[10])
{
	char c;
	for (int i = 0; i < 10; i++)
		printf("%d ", BCoord[i]);
	for(int i = 0; i < 10; i++)
	{
		int c = i + '0';
		write(1, "  ", 2);
		write(1, &c, 1);
		write(1, "  ", 2);
	}
	write(1, "\n\n", 2);
	for (int i = 0; i < 10; i++)
	{
		c = i + '0';
		write(1, &c, 1);
		write(1, "   ", 3);
		for (int j = 0; j < 10; j++)
		{
			write(1, &matrix[i][j], 1);
			write(1, "    ", 4);
		}
		printf("\n\n");
	}
}

void takeCoord(char matrix[11][11], bool **sentinel, int BCoord[10])
{
	int coord = -2;
	int par1, par2;

	scanf("%d", &coord);
	for (int i = 0; i < 10; i++)
		if (BCoord[i] == coord)
		{
			**sentinel = true;
			par1 = coord / 10;
			par2 = coord % 10;
			matrix[par1][par2] = 'B';
			display(matrix, BCoord);
		}
	if (**sentinel == false)
	{
		par1 = coord / 10;
		par2 = coord % 10;
		int nbr = find_nbr(matrix, coord, BCoord);
		char c =  nbr + '0';
		matrix[par1][par2] = c;
		display(matrix, BCoord);
	}
}

void displayp(char matrix[11][11], bool *sentinel, int BCoord[10])
{
	char c;
	int count = 0;
	for(int i = 0; i < 10; i++)
	{
		int c = i + '0';
		write(1, "   ", 2);
		write(1, &c, 1);
		write(1, "  ", 2);
	}
	write(1, "\n\n", 2);
	for (int i = 0; i < 10; i++)
	{
		c = i + '0';
		write(1, &c, 1);
		write(1, "   ", 3);
		for (int j = 0; j < 10; j++)
		{
			write(1, &matrix[i][j], 1);
			write(1, "    ", 4);
		}
		printf("\n\n");
	}
	while (*sentinel == false)
	{
		takeCoord(matrix, &sentinel, BCoord);
		count++;
		if (count == 90)
		{
			printf("VITTORIA!");
			break;
		}
	}
	if (*sentinel == true)
		printf("GAME OVER!");
}

int main()
{
	srand(time(NULL));
	bool sentinel = false;
	bool cond1, cond2;
	char matrix[11][11];
	int BCoord[10];

	for(int i = 0; i < 10; i++)
	{
		BCoord[i] = rand() % 100;
		for (int j = i; j > 0; j--)
			if (BCoord[i] == BCoord[j - 1])
			{
				i--;
				break;
			}
		printf("%d ", BCoord[i]);
	}
	write(1, "  ", 2);
	for(int i = 0; i < 11; i++)
	{
		for(int j = 0; j < 11; j++)
			matrix[i][j] = '*';
	}
	displayp(matrix, &sentinel, BCoord);
}