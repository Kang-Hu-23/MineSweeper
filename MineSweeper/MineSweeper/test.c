#include"MineSweeper.h"

int main()
{
	int length = 9;
	int width = 9;
	int mine = 10;
	int judge = -1;
	SetLoc();
	Menu();
	SetGam(&width,&length,&mine);
	system("cls");
	int ** arr_invisible = InitInviMatrix(width, length);
	PutMine(width ,length ,mine ,arr_invisible);
	PutNum(width ,length, mine, arr_invisible);
	CreatMap(width, length);
	do
	{
		MouseClickInfo clickInfo = getMouseClick();
		if (clickInfo.buttonType == 'L') 
		{
			LeftJudge(width, length, &judge, arr_invisible, clickInfo);
		}
		else if (clickInfo.buttonType == 'R') 
		{
			RightJudge(width, length, arr_invisible, clickInfo);
		}
		Check(width,length,&judge,arr_invisible);
		if (judge == 1)
		{
			SetPos(0, 10);
			printf("Excellent!");
			return 0;
		}
		if (judge == 0)
		{
			SetPos(0,10);
			printf("Failed");
			return 0;
		}
		/*SetPos(0, 13);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < lenth; j++)
			{
				printf("%d ", arr_invisible[i][j]);
			}
			printf("\n");
		}*/
	} while (1);
	return 0;
}