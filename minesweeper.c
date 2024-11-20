#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROW 20  // 行数
#define COL 20  // 列数
#define ROW1 (ROW + 2)
#define COL1 (COL + 2)
#define MINE_COUNT 100  // 雷数
#define UNOPENED_CELL '#'  // 未翻开格子的
#define MINE_CELL '*'    // 雷的
#define EMPTY_CELL '0'   // 周围无雷
#define MAX_DEPTH 5      // 最大递归深度

// 打印菜单
void menu() {
    printf("**********  扫雷  ***********\n");
    printf("*****************************\n");
    printf("*******  按任意键进入*********\n");
    printf("********* 按 j 退出 *********\n");
}

// 初始化棋盘
void initBoard(char board[ROW1][COL1], int row, int col, char set) 
{
    for (int i = 0; i < row; i++) 
    {
        for (int j = 0; j < col; j++) 
        {
            board[i][j] = set;
        }
    }
}

// 打印棋盘，设置颜色
void printBoard(char board[ROW1][COL1], int row, int col) 
{
    int i, j;
    printf("*************************************************\n");
    printf("\n\n\n");
    for (i = 0; i <= col; i++) 
    {
        if (i < 10) 
        {
            printf("%d  ", i);
        } else if (i >= 10 && i < 100) 
        {
            printf("%d ", i);
        } else 
        {
            printf("%d", i);
        }
    }
    printf("\n");
    for (i = 1; i <= row; i++) 
    {
        if (i < 10) 
        {
            printf("%d  ", i);
        } 
        else if (i >= 10 && i < 100) 
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
            if (board[i][j] == UNOPENED_CELL) 
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            // 设置雷的显示颜色（这里设置为红色）
            else if (board[i][j] == MINE_CELL) 
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

// 在棋盘上随机布置雷
void plantMines(char board[ROW1][COL1], int row, int col) 
{
    int count = MINE_COUNT;
    while (count > 0) 
    {
        int x = rand() % row + 1;
        int y = rand() % col + 1;
        if (board[x][y] == EMPTY_CELL) 
        {
            board[x][y] = MINE_CELL;
            count--;
        }
    }
}

// 判断坐标是否在棋盘范围内
int isInBoard(int row, int col) 
{
    return row >= 0 && row < ROW1 && col >= 0 && col < COL1;
}

// 统计指定坐标周围的地雷数量，递归实现，限制最大递归深度
int countMines(char board[ROW1][COL1], char displayBoard[ROW1][COL1], int row, int col, int depth, int max_depth) 
{
    int count = 0;
    if (board[row][col]!= MINE_CELL) 
    {
        if (depth < max_depth) 
        {
            for (int i = (row > 0? row - 1 : 0); i <= (row < ROW1 - 1? row + 1 : ROW1 - 1); i++) 
            {
                for (int j = (col > 0? col - 1 : 0); j <= (col < COL1 - 1? col + 1 : COL1 - 1); j++) 
                {
                    if (i!= row || j!= col) 
                    {
                        if (board[i][j] == MINE_CELL) 
                        {
                            count++;
                        } else 
                        {
                            // 如果周围格子是空白格且未被统计过
                            if (displayBoard[i][j] == UNOPENED_CELL) 
                            {
                                int sub_count = countMines(board, displayBoard, i, j, depth + 1, max_depth);
                                count += sub_count;
                            }
                        }
                    }
                }
            }
        }
        displayBoard[row][col] = (count == 0)? EMPTY_CELL : (count + '0');  // 如果周围没雷设置为空，否则设置为数字字符
    }
    return count;
}

// 处理玩家输入坐标进行排雷操作
void inputAndSweep(char mineBoard[ROW1][COL1], char displayBoard[ROW1][COL1], int row, int col) 
{
    int x, y;
    int unopenedCells = ROW * COL - MINE_COUNT;  // 剩余未翻开格子数量
    while (unopenedCells > 0) 
    {
        printf("请输入坐标：->\n");
        scanf("%d %d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col) 
        {
            if (mineBoard[x][y] == MINE_CELL) 
            {
                // 踩到地雷，游戏结束
                printf("很遗憾，你被炸死了！\n");
                break;
            } 
            else 
            {
                int count = countMines(mineBoard, displayBoard, x, y, 0, MAX_DEPTH);
                // 如果翻开的是空白格（周围无雷），自动翻开周围空白格（递归处理）
                if (displayBoard[x][y] == EMPTY_CELL) 
                {
                    for (int i = (x > 0? x - 1 : 0); i <= (x < ROW1 - 1? x + 1 : ROW1 - 1); i++) 
                    {
                        for (int j = (y > 0? y - 1 : 0); j <= (y < COL1 - 1? y + 1 : COL1 - 1); j++) 
                        {
                            if (displayBoard[i][j] == UNOPENED_CELL) 
                            {
                                countMines(mineBoard, displayBoard, i, j, 0, MAX_DEPTH);
                            }
                        }
                    }
                }
                // 打印更新显示棋盘后的提示信息，并调用函数打印当前棋盘状态
                printf("更新坐标 (%d, %d) 的显示信息后，当前棋盘状态如下：\n", x, y);
                printBoard(displayBoard, ROW, COL);
                unopenedCells = 0;
                // 重新统计剩余未翻开格子数量
                for (int i = 1; i <= row; i++) 
                {
                    for (int j = 1; j <= col; j++) 
                    {
                        if (displayBoard[i][j] == UNOPENED_CELL) 
                        {
                            unopenedCells++;
                        }
                    }
                }
            }
        } 
        else 
        {
            // 坐标非法，提示重新输入
            printf("坐标非法，请重新输入！\n");
        }
    }
    if (unopenedCells == 0) 
    {
        // 排雷成功提示
        printf("恭喜你，排雷成功！\n");
        printBoard(mineBoard, ROW, COL);   
    }
}

// 游戏主流程
void game() {
    char mineBoard[ROW1][COL1];
    char displayBoard[ROW1][COL1];
    initBoard(mineBoard, ROW1, COL1, EMPTY_CELL);
    initBoard(displayBoard, ROW1, COL1, UNOPENED_CELL);
    plantMines(mineBoard, ROW, COL);
    printBoard(displayBoard, ROW, COL);
    inputAndSweep(mineBoard, displayBoard, ROW, COL);
}

int main() 
{
    srand((unsigned int)time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
    menu();
    char choice;
    do {
        choice = getchar();
        if (choice!= '\n') 
        {  // 避免直接按回车键导致多余的循环
            if (choice == 'j') 
            {
                break;
            } else {
                game();
            }
        }
    } while (1);
    return 0;
}