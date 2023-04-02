#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

char direction = 0;
int foodx = 0;
int foody = 0;
int score = 0;

int wrongfood(snake *asnake)
{
    int res = 0;
    asnake = asnake->pN;
    for (; asnake != NULL ; asnake = asnake->pN)
    {
        if (asnake->x == foodx && asnake->y == foody)
        {
            res = 1;
            break;
        }
    }
    return res;
    
}

void newfood(snake *asnake)
{
    do
    {
        srand((unsigned)time(NULL));
        foody = 1 + rand() % 19;
        foodx = 1 + rand() % 19;
        
        /* code */
    } while (wrongfood(asnake));
}

// 初始化一条蛇 长度为三    x y 是窗口大小
snake * init_snake(int sizex , int sizey)
{
    int x , y;
    x = sizex / 2;
    y = sizey / 2;
    snake *asnake;
    snake *temple;
    snake *new;

    asnake = malloc(sizeof(snake));
    temple = asnake;

    for (int i = 0 ; i < 3 ; i++)
    {
        new = malloc(sizeof(snake));
        new->x = x;
        new->y = y;
        new->pN = NULL;

        temple->pN = new;

        temple = temple->pN;
        
        y++;
    }
    direction = 'u'; // up 向上
    newfood(asnake);
    return asnake;
}


// 画蛇
void drawSnake(snake *asnake , WINDOW *win)
{
    // 判断方向 绘制头
    char head = '@';
    switch (direction)
    {
    case 'u':
        head = 'A';
        break;
    case 'd':
        head = 'V';
        break;

    case 'r':
        head = '>';
        break;

    case 'l':
        head = '<';
        break;

    default:
        break;
    }

    char strhead[2] = {head , '\0'};
    asnake = asnake->pN;    // 头节点不存东西
    mvwprintw(win , asnake->y , asnake->x , strhead);   // 画头
    asnake = asnake->pN;
    for (; asnake != NULL ; asnake = asnake->pN)
    {
        mvwprintw(win , asnake->y , asnake->x , "@");
    }
    wrefresh(win);
}

void delLastOne(snake *asnake , WINDOW *win)
{
    snake *last;
    snake *last2;

    last = asnake->pN;
    last2 = asnake;

    for (; last->pN != NULL ; last = last->pN)
    {
        last2 = last2->pN;
    }
    mvwprintw(win , last->y , last->x , " ");
    free(last);
    last2->pN = NULL;
}

void moveSnake(char direction , snake *asnake , WINDOW *win)
{
    snake *snakehead = asnake->pN; // 头节点不存东西
    int headx = snakehead->x;
    int heady = snakehead->y;

    int newx , newy;
    newx = headx;
    newy = heady;

    switch (direction)
    {
    case 'u':
        newy--;
        break;
    
    case 'd':
        newy++;
        break;

    case 'r':
        newx++;
        break;

    case 'l':
        newx--;
        break;

    default:
        break;
    }

    // 插入新节点
    snake *pnew;
    pnew = malloc(sizeof(snake));
    pnew->x = newx;
    pnew->y = newy;
    pnew->pN = snakehead;

    asnake->pN = pnew;
    delLastOne(asnake , win);
}

int crash(snake *asnake , char inputc)
{
    asnake = asnake->pN;
    int headx = asnake->x;
    int heady = asnake->y;
    asnake = asnake->pN;
    int x2 = asnake->x;
    int y2 = asnake->y;

    switch (inputc)
    {
    case 'w':
        heady--;
        break;
    
    case 's':
        heady++;
        break;

    case 'a':
        headx--;
        break;

    case 'd':
        headx++;
        break;

    default:
        break;
    }
    if (headx == x2 && heady == y2)
    { return 0; }
    else
    { return 1; }
}

// 获取蛇的输入
void getInput(snake *asnake , WINDOW *win)
{
    char c;
    c = getch();
    if (c != ERR && (c == 'w' || c == 's' || c == 'a' || c == 'd') && crash(asnake , c))
    {
        switch (c)
        {
        case 'w':
            direction = 'u';
            break;

        case 's':
            direction = 'd';
            break;

        case 'a':
            direction = 'l';
            break;

        case 'd':
            direction = 'r';
            break;
        
        default:
            break;
        }
    }
    moveSnake(direction , asnake , win);
}

void snakegrow(snake *asnake)
{
    for (; asnake->pN->pN != NULL ; asnake = asnake->pN)
    {}
    snake *new = malloc(sizeof(snake));
    new->x = asnake->pN->x*2 - asnake->x;
    new->y = asnake->pN->y*2 - asnake->y;
    new->pN = NULL;
    asnake->pN->pN = new;
}

int check(snake *asnake)
{
    int res = 0;    // 0代表正常 1代表吃到食物 -1代表越界死 -2代表吃到自己
    // 吃到食物
    int headx = asnake->pN->x;
    int heady = asnake->pN->y;

    if (headx == foodx && heady == foody)
    {
        res = 1;
        snakegrow(asnake);
    }

    // 检查是否越界
    if (headx >= 21 || headx <= 0 || heady >= 21 || heady <= 0)
    {
        res = -1;
    }
    // 是否吃到自己
    asnake = asnake->pN->pN;
    for (; asnake != NULL ; asnake = asnake->pN)
    {
        if (asnake->x == headx && asnake->y == heady)
        {
            res = -2;
            break;
        }
    }
    return res;
}


void drawFood(WINDOW *win)
{
    mvwprintw(win , foody , foodx , "x");
}


void printsign(WINDOW *win , int y , int x)
{
    mvwprintw(win , 1 , 1 , "+");
    mvwprintw(win , y - 2 , 1 , "+");
    mvwprintw(win , 1 , x - 2 , "+" );
    mvwprintw(win , y - 2 , x - 2 , "+");
}


void drawScore(WINDOW *win)
{
    mvwprintw(win , 1 , 1 ,  "score:%d" , score);
    wrefresh(win);
}


void Draw(WINDOW *win , snake *asnake , int x , int y)
{
    printsign(win , y , x);
    drawFood(win);
    drawSnake(asnake , win);
}


int Trigger(WINDOW *win , WINDOW *scorewin , snake *asnake)
{
    int res = 0;
    getInput(asnake , win);
    int i = 0;
    i = check(asnake);
    res = i;
    switch (i)
    {
    case 1: // 吃到食物
        newfood(asnake);
        score++;
        drawScore(scorewin);
        break;
    
    case -1:
    case -2:    // 两种死
        break;

    default:
        break;
    }
    return res;
}
