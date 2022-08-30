#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable: 4996)
#define StageX 20
#define StageY 40

char Stage[StageX][StageY];

struct
{
	int posX[255];
	int posY[255];
	int size;
}ply;

struct
{
	int posX;
	int posY;
}food;

int main(void)
{
	for (int i = 0; i < StageX; i++)
	{
		if (i == 0 || i == StageX - 1)
			strcpy(Stage[i], "***************************************");
		else
			strcpy(Stage[i], "*                                     *");
	}
	ply.posX[0] = StageX / 2;
	ply.posY[0] = StageY / 2;
	ply.size = 3;
	Stage[ply.posX[0]][ply.posY[0]] = 'O';
	srand((unsigned)time(0));
	food.posX = 2 + rand() % (StageX - 3);
	food.posY = 2 + rand() % (StageY - 4);
	Stage[food.posX][food.posY] = 'F';
	int score = 0;
	for (int i = 0; i < StageX; i++)
		printf("%s\n", Stage[i]);
	printf("Score: %d", score);
	while (1)
	{
		char key = getch();
		while (!kbhit())
		{
			if (ply.posX[0] < 2 || ply.posX[0] > StageX - 3 || ply.posY[0] < 2 || ply.posY[0] > StageY - 4)
			{
				char gameover[11] = "\nGame Over!";
				for (int i = 0; i < 10; i++)
				{
					Sleep(200);
					printf("%c", gameover[i]);
				}
				Sleep(1500);
				return 0;
			}
			for (int i = 2; i < ply.size; i++)
			{
				if (ply.posX[0] == ply.posX[i] && ply.posY[0] == ply.posY[i])
				{
					char gameover[11] = "\nGame Over!";
					for (int i = 0; i < 10; i++)
					{
						Sleep(200);
						printf("%c", gameover[i]);
					}
					Sleep(1500);
					return 0;
				}
			}
			for (int i = 0; i < ply.size; i++)
				Stage[ply.posX[i]][ply.posY[i]] = ' ';
			switch (key)
			{
				case 'w':
				{
					Stage[ply.posX[0]--][ply.posY[0]];
					break;
				}
				case 's':
				{
					Stage[ply.posX[0]++][ply.posY[0]];
					break;
				}
				case 'a':
				{
					Stage[ply.posX[0]][ply.posY[0]--];
					break;
				}
				case 'd':
				{
					Stage[ply.posX[0]][ply.posY[0]++];
					break;
				}
				case 'q':
					return 0;
			}
			int headX = ply.posX[0];
			int headY = ply.posY[0];
			if (ply.posX[0] == food.posX && ply.posY[0] == food.posY)
			{
				ply.size++;
				score += 10;
				srand((unsigned)time(0));
				food.posX = 2 + rand() % (StageX - 3);
				food.posY = 2 + rand() % (StageY - 4);
				Stage[food.posX][food.posY] = 'F';
			}
			for (int i = 1; i < ply.size; i++)
			{
				int tailX = ply.posX[i];
				int tailY = ply.posY[i];
				ply.posX[i] = headX;
				ply.posY[i] = headY;
				headX = tailX;
				headY = tailY;
				Stage[ply.posX[i]][ply.posY[i]] = 'o';
			}
			system("cls");
			Stage[ply.posX[0]][ply.posY[0]] = 'O';
			for (int i = 0; i < StageX; i++)
				printf("%s\n", Stage[i]);
			printf("Score: %d", score);
			Sleep(200);
		}
	}
	return 0;
}