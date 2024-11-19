#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define ROW 20//行
#define COL 20//列
#define ROW1 ROW+2
#define COL1 COL+2
#define WAING 200//雷的个数
#define EA '0'
#define EB '#'
#define EC '*'
#define ED '1'
#define MAX_DEPTH 9//最大递归深度



void meau()
{
    printf("**********  扫雷  ***********\n");
    printf("*****************************\n");
    printf("*******  按任意键进入*********\n");
    printf("********* 按 j退出 *********\n");
}

void subboard(char board[ROW1][COL1], int row, int col, char set)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            board[i][j] = set;
        }
    }
}

void printboard(char board[ROW1][COL1], int row, int col)
{
    int i = 0;
    int j = 0;
    printf("*************************************************\n");
    printf("\n\n\n");
    for ( i = 0; i <= col; i++)
    {
        if(i<10)
        {
            printf("%d  ", i);
        }
        else if(i>=10&&i<100)
        {
            printf("%d ", i);
        }
        else
        {
            printf("%d", i);
        }
    }
    printf("\n");
    for (i = 1; i <= row; i++)
    {
        if(i<10)
        {
            printf("%d  ", i);
        }
        else if(i>=10&&i<100)
        {
            printf("%d ", i);
        }
        else
        {
            printf("%d", i);
        }
        for (j = 1; j <= col; j++) 
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // 设置未翻开格子的显示颜色（这里设置为蓝色）
            if (board[i][j] == EB) 
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            // 设置雷的显示颜色（这里设置为红色）
            else if (board[i][j] == ED) 
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            // 设置已翻开空白格及数字的显示颜色（这里设置为白色）
            else 
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            printf("%c  ", board[i][j]);
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n");
    }
}

void numboard(char board[ROW1][COL1], int row, int col)
{
    int count = WAING;
    while (count)
    {
        int x = rand() % row + 1;
        int y = rand() % col + 1;
        if (board[x][y] == EA)
        {
            board[x][y] = ED;
            count--;
        }
    }
}

int isInBoard(int row, int col) 
{
    return row >= 0 && row < ROW1 && col >= 0 && col < COL1;
}


// 递归统计九宫格雷数的核心函数，控制深度避免无限递归，修正雷判断条件并优化边界处理（可选）
int countMines(char board[ROW1][COL1], int row, int col, int depth) 
{
    // 递归终止条件：深度超出限制或者坐标超出棋盘范围
    if (depth > MAX_DEPTH ||!isInBoard(row, col)) 
    {
        return 0;
    }
    int count = 0;
    // 修正此处，判断是否为雷的字符
    if (board[row][col] == ED) 
    {
        count++;
    }
    // 优化的周围九宫格遍历方式（可选），避免不必要的边界外判断
    for (int i = (row > 0? row - 1 : 0); i <= (row < ROW - 1? row + 1 : ROW - 1); i++) 
    {
        for (int j = (col > 0? col - 1 : 0); j <= (col < COL - 1? col + 1 : COL - 1); j++) 
        {
            if (i!= row || j!= col) 
            {
                count += countMines(board, i, j, depth + 1);
            }
        }
    }
    return count;
}

void scanfboard(char mine[ROW1][COL1],char show [ROW1][COL1] ,int row, int col)
{
    int x = 0;
    int y = 0;
    int win = 0;
    while (1)
    {
        printf("请输入坐标：->\n");
        scanf("%d %d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col)
        {
            if (mine[x][y] == ED)
            {
                printf("很遗憾，你被炸死了！\n");
                break;
            }
            else
            {
                int count = countMines(mine, x, y, 0);
                show[x][y] = count;
                printboard(show, ROW, COL);
            }
        }
        else
        {
            printf("坐标非法，请重新输入！\n");
        }
        win++;
    }
    if (win == ROW * COL - WAING)
    {
        printf("恭喜你，排雷成功！\n");
    }
    else
    {
        printf("很遗憾，你没有排雷成功！\n");
    }
}
void game()
{
    char mine[ROW1][COL1] = { 0 };
    char show[ROW1][COL1] = { 0 };
    subboard(mine, ROW1, COL1, EA);
    subboard(show, ROW1, COL1, EB);
    //初始化棋盘
    numboard(mine, ROW, COL);
    //布置雷子
    printboard(show, ROW, COL);
    
   // printboard(mine, ROW, COL);
    //打印棋盘
    scanfboard(mine,show, ROW, COL);
    //扫雷
}

int main()
{
    srand((unsigned  int)time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
    meau();
    char num;
    do
    {
        num = getchar();
        game();
    } while (num!='j');
    
    return 0;
}