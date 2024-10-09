#include"MineSweeper.h"

void SetLoc()
{
    setlocale(LC_ALL, "");//切换到本地环境
}

void SetCmd()
{
	system("mode con cols=150 lines=40");//设置命令窗口大小150,40
	system("title 扫雷游戏");//设置窗口标题
}

void SetPos(short x, short y)
{
    //设置光标位置
	COORD pos = { x,y };
	HANDLE Houtput = NULL;
	Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Houtput, pos);
}

void Menu()
{
    //打印菜单
	SetPos(65, 8);
	printf("欢迎来到扫雷小游戏");
	SetPos(65, 30);
	system("pause");
	system("cls");
}

void SetGam(int* x, int* y, int* z)
{
    printf("请输入宽度");
    scanf_s("%d", x);
    printf("请输入长度");
    scanf_s("%d", y);
    printf("请输入地雷数量");
    scanf_s("%d", z);
}

int** InitInviMatrix(int x ,int y)
{
    // 使用动态内存分配创建二维数组
    //行
    int** arr_invisible = (int**)malloc(x * sizeof(int*));
    //列
    for (int i = 0; i < x; i++)
    {
        arr_invisible[i] = (int*)malloc(y * sizeof(int));
    }

    // 初始化数组
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            arr_invisible[i][j] = 0;  // 初始化为0
        }
    }
    return arr_invisible;
}

void PutMine(int x, int y, int mine, int** arr_invisible)
{
    for (int i = 1; i <= mine; i++)
    {
        unsigned int seed = (unsigned int)clock();
        srand(seed); // 用当前时间初始化随机数生成器
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
    //遍历数组
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            //计算周围的地雷数 并 限制其不越界访问
            if (arr_invisible[i][j] == 0 && i >= 1 && i <= y-2 && j >=1 && j <= x-2)
            {
                for (int rowhead = i - 1; rowhead <= i + 1; rowhead++)
                {
                    for (int colhead = j - 1; colhead <= j + 1; colhead++)
                    {
                        if (arr_invisible[rowhead][colhead] == 9)
                        {
                            //数组9代表地雷，若有9则自增一次
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
    // 获取标准输入句柄
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    // 获取当前控制台模式，以便稍后恢复
    GetConsoleMode(hInput, &prevMode);

    // 启用鼠标输入并禁用快速编辑模式
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    INPUT_RECORD inputRecord;
    DWORD events;  // 存储事件数量

    MouseClickInfo clickInfo = { { -1, -1 }, 'N' };  // 初始化，默认无点击

    while (1) {
        // 等待输入事件
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        // 检测是否为鼠标事件
        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

            // 检测左键是否被按下
            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                clickInfo.position.x = mouseEvent.dwMousePosition.X;
                clickInfo.position.y = mouseEvent.dwMousePosition.Y;
                clickInfo.buttonType = 'L';  // 左键
                break;
            }

            // 检测右键是否被按下
            if (mouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
                clickInfo.position.x = mouseEvent.dwMousePosition.X;
                clickInfo.position.y = mouseEvent.dwMousePosition.Y;
                clickInfo.buttonType = 'R';  // 右键
                break;
            }
        }
    }

    // 恢复原来的控制台模式
    SetConsoleMode(hInput, prevMode);

    return clickInfo;
}

void Unflod(int x, int y, int** arr_invisible, MouseClickInfo clickInfo)
{
    if (arr_invisible[clickInfo.position.y - 1][clickInfo.position.x / 2 - 1] != 9)
    {
        //把光标设置在点击格子的右上一格
        for (int a = (int)(clickInfo.position.y - 2); a <= clickInfo.position.y; a++)
        {
            for (int b = (int)(clickInfo.position.x / 2 - 2); b <= clickInfo.position.x / 2; b++)
            {
                //记录右上一格的位置
                    MouseClickInfo clickInfo1 = { 0 };
                    clickInfo1.position.y = a + 1;
                    clickInfo1.position.x = (b + 1) * 2 + 1;
                    //如果越界访问则判断下一格
                    if (a < 0 || b < 0 || a >= y || b >= x)
                    {
                        continue;
                    }
                    //如果无地雷，消除方块，标记为-1，表示判断过该格子，再以自身为中心展开
                    else if (arr_invisible[a][b] == 0)
                    {
                        SetPos((short int)clickInfo1.position.x - 1, (short int)clickInfo1.position.y);
                        printf("  ");
                        arr_invisible[a][b] = -1;
                        Unflod(x, y, arr_invisible, clickInfo1);
                    }
                    //如果是显示周围地雷数的格子，则显示地雷数，再将该格子记为-1，表示判断过该格子
                    else if (arr_invisible[a][b] != 0 && arr_invisible[a][b] != -1)
                    {
                        SetPos((short int)clickInfo1.position.x - 1, (short int)clickInfo1.position.y);
                        printf("%d ", arr_invisible[a][b]);
                        arr_invisible[a][b] = -1;
                        continue;
                    }
                    //判断过的格子不做判断，进入下一格
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