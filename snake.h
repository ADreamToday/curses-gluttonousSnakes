typedef struct snake
{
    int x;
    int y;
    struct snake *pN;
}snake;

extern snake *init_snake(int sizex , int sizey);
extern int Trigger(WINDOW *win , WINDOW *scorewin , snake *asnake);
extern void Draw(WINDOW *win , snake *asnake , int x , int y);
extern void drawScore(WINDOW *win);
