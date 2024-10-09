#include"MineSweeper.h"

void SetLoc()
{
    setlocale(LC_ALL, "");//�л������ػ���
}

void SetCmd()
{
	system("mode con cols=150 lines=40");//��������ڴ�С150,40
	system("title ɨ����Ϸ");//���ô��ڱ���
}

void SetPos(short x, short y)
{
    //���ù��λ��
	COORD pos = { x,y };
	HANDLE Houtput = NULL;
	Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Houtput, pos);
}

void Menu()
{
    //��ӡ�˵�
	SetPos(65, 8);
	printf("��ӭ����ɨ��С��Ϸ");
	SetPos(65, 30);
	system("pause");
	system("cls");
}

void SetGam(int* x, int* y, int* z)
{
    printf("��������");
    scanf_s("%d", x);
    printf("�����볤��");
    scanf_s("%d", y);
    printf("�������������");
    scanf_s("%d", z);
}

int** InitInviMatrix(int x ,int y)
{
    // ʹ�ö�̬�ڴ���䴴����ά����
    //��
    int** arr_invisible = (int**)malloc(x * sizeof(int*));
    //��
    for (int i = 0; i < x; i++)
    {
        arr_invisible[i] = (int*)malloc(y * sizeof(int));
    }

    // ��ʼ������
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            arr_invisible[i][j] = 0;  // ��ʼ��Ϊ0
        }
    }
    return arr_invisible;
}

void PutMine(int x, int y, int mine, int** arr_invisible)
{
    for (int i = 1; i <= mine; i++)
    {
        unsigned int seed = (unsigned int)clock();
        srand(seed); // �õ�ǰʱ���ʼ�������������
        int cols = rand() % x;
        int rows = rand() % y;
        if (arr_invisible[rows][cols] == 9)
        {
            i--;
        }
        arr_invisible[rows][cols] = 9;
    }
    /*for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%d ", arr_invisible[i][j]);
        }
        printf("\n");
    }*/
}

void PutNum(int x, int y, int mine, int** arr_invisible)
{
    //��������
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            //������Χ�ĵ����� �� �����䲻Խ�����
            if (arr_invisible[i][j] == 0 && i >= 1 && i <= y-2 && j >=1 && j <= x-2)
            {
                for (int rowhead = i - 1; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            //����9������ף�����9������һ��
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if(arr_invisible[i][j] == 0 && i == 0 && j == 0)
            {
                for (int rowhead = i; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if(arr_invisible[i][j] == 0 && i == 0 && j == x - 1)
            {
                for (int rowhead = i; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if(arr_invisible[i][j] == 0 && i == y - 1 && j == x - 1)
            {
                for (int rowhead = i - 1; rowhead <= i; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if(arr_invisible[i][j] == 0 && i == y - 1 && j == 0)
            {
                for (int rowhead = i - 1; rowhead <= i; rowhead++)
                {
                    for (int colhead = j; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if (arr_invisible[i][j] == 0 && i == 0 && j != 0 && j!= x-1)
            {
                for (int rowhead = i; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if (arr_invisible[i][j] == 0 && j == 0 && i !=0 && i != y-1)
            {
                for (int rowhead = i - 1; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if (arr_invisible[i][j] == 0 && j == x - 1 && i !=0 && i != y-1)
            {
                for (int rowhead = i - 1; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
            else if(arr_invisible[i][j] == 0 && i == y - 1 && j != 0 && j != x - 1)
            {
                for (int rowhead = i - 1; rowhead <= i; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            arr_invisible[i][j]++;
                        }
                    }
                }
            }
        }
    }
    /*SetPos(0, 13);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            printf("%d ", arr_invisible[i][j]);
        }
        printf("\n");
    }*/
}

void CreatMap(int x, int y)
{
    SetPos(0,0);
    for (int i = 0; i <= y; i++)
    {
        printf("%d " ,i);
        printf("\n");
    }
    SetPos(0, 0);
    for (int j = 0; j <= x; j++)
    {
        if (j < 10)
        {
            printf("%d ", j);
        }
        else
        {
            printf("%d", j);
        }
    }
    SetPos(2, 1);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            wprintf(L"%lc" ,WALL);
        }
        SetPos(2,i+2);
    }

}

MouseClickInfo getMouseClick() {
    // ��ȡ��׼������
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    // ��ȡ��ǰ����̨ģʽ���Ա��Ժ�ָ�
    GetConsoleMode(hInput, &prevMode);

    // ����������벢���ÿ��ٱ༭ģʽ
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    INPUT_RECORD inputRecord;
    DWORD events;  // �洢�¼�����

    MouseClickInfo clickInfo = { { -1, -1 }, 'N' };  // ��ʼ����Ĭ���޵��

    while (1) {
        // �ȴ������¼�
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        // ����Ƿ�Ϊ����¼�
        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

            // �������Ƿ񱻰���
            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                clickInfo.position.x = mouseEvent.dwMousePosition.X;
                clickInfo.position.y = mouseEvent.dwMousePosition.Y;
                clickInfo.buttonType = 'L';  // ���
                break;
            }

            // ����Ҽ��Ƿ񱻰���
            if (mouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
                clickInfo.position.x = mouseEvent.dwMousePosition.X;
                clickInfo.position.y = mouseEvent.dwMousePosition.Y;
                clickInfo.buttonType = 'R';  // �Ҽ�
                break;
            }
        }
    }

    // �ָ�ԭ���Ŀ���̨ģʽ
    SetConsoleMode(hInput, prevMode);

    return clickInfo;
}

void Unflod(int x, int y, int** arr_invisible, MouseClickInfo clickInfo)
{
    if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 9)
    {
        //�ѹ�������ڵ�����ӵ�����һ��
        for (int a = (int)(clickInfo.position.y - 2); a <= clickInfo.position.y; a++)
        {
            for (int b = (int)(clickInfo.position.x / 2 - 2); b <= clickInfo.position.x / 2; b++)
            {
                //��¼����һ���λ��
                    MouseClickInfo clickInfo1 = { 0 };
                    clickInfo1.position.y = a + 1;
                    clickInfo1.position.x = (b + 1) * 2 + 1;
                    //���Խ��������ж���һ��
                    if (a < 0 || b < 0 || a >= y || b >= x)
                    {
                        continue;
                    }
                    //����޵��ף��������飬���Ϊ-1����ʾ�жϹ��ø��ӣ���������Ϊ����չ��
                    else if (arr_invisible[a][b] == 0)
                    {
                        SetPos((short int)clickInfo1.position.x - 1, (short int)clickInfo1.position.y);
                        printf("  ");
                        arr_invisible[a][b] = -1;
                        Unflod(x, y, arr_invisible, clickInfo1);
                    }
                    //�������ʾ��Χ�������ĸ��ӣ�����ʾ���������ٽ��ø��Ӽ�Ϊ-1����ʾ�жϹ��ø���
                    else if (arr_invisible[a][b] != 0 && arr_invisible[a][b] != -1)
                    {
                        SetPos((short int)clickInfo1.position.x - 1, (short int)clickInfo1.position.y);
                        printf("%d ", arr_invisible[a][b]);
                        arr_invisible[a][b] = -1;
                        continue;
                    }
                    //�жϹ��ĸ��Ӳ����жϣ�������һ��
                    else
                    {
                        continue;
                    }
            }
        }
    }
}

void LeftJudge(int x, int y, int* z, int** arr_invisible, MouseClickInfo clickInfo)
{
    if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] == 0 && clickInfo.position.x % 2 != 0)
    {
        SetPos((short int)clickInfo.position.x - 1, (short int)clickInfo.position.y);
        printf("  ");
        Unflod(x, y, arr_invisible, clickInfo);
    }
    else if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] == 0 && clickInfo.position.x % 2 == 0)
    {
        SetPos((short int)clickInfo.position.x, (short int)clickInfo.position.y);
        printf("  ");
        Unflod(x, y, arr_invisible, clickInfo);
    }

    else if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 0 && clickInfo.position.x % 2 == 0 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 9 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != -1 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != -2)
    {
        SetPos((short int)clickInfo.position.x, (short int)clickInfo.position.y);
        printf("%d ", arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1]);
        
    }
    else if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 0 && clickInfo.position.x % 2 != 0 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 9 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != -1 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != -2)
    {
        SetPos((short int)clickInfo.position.x - 1, (short int)clickInfo.position.y);
        printf("%d ", arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1]);
        
    }
    else if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] == -2)
    {
        SetPos((short int)clickInfo.position.x, (short int)clickInfo.position.y);
        wprintf(L"%lc", WALL);
        arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] = 9;
    }
    else if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] == 9)
    {
        *z = 0;
    }
    
}

void RightJudge(int x, int y, int** arr_invisible, MouseClickInfo clickInfo)
{
    if (clickInfo.position.x % 2 != 0 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 9 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != -1)
    {
        SetPos((short int)clickInfo.position.x - 1, (short int)clickInfo.position.y);
        printf("* ");
    }
    else if (clickInfo.position.x % 2 == 0 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 9 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != -1)
    {
        SetPos((short int)clickInfo.position.x, (short int)clickInfo.position.y);
        printf("* ");
    }
    else if (clickInfo.position.x % 2 != 0 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] == 9)
    {
        SetPos((short int)clickInfo.position.x - 1, (short int)clickInfo.position.y);
        printf("* ");
        arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] = -2;
    }
    else if (clickInfo.position.x % 2 == 0 && arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] == 9)
    {
        SetPos((short int)clickInfo.position.x, (short int)clickInfo.position.y);
        printf("* ");
        arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] = -2;
    }
}

void Check(int x, int y, int*z, int** arr_invisible)
{
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (arr_invisible[i][j] == 9)
            {
                count1++;
            }
            if (arr_invisible[i][j] == -3)
            {
                count2++;
            }
        }
    }
    if (count1 == 0 && count2 == 0)
    {
        *z = 1;
    }
}