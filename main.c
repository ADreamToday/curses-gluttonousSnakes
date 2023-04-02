#include <curses.h>
#include <string.h>
#include "snake.h"
#include <stdlib.h>


int main()
{  
    initscr();
    noecho();
    curs_set(0);    // 光标不可见
    // halfdelay(5);
    timeout(400);
    cbreak();
    WINDOW *gameWin;
    WINDOW *scoreWin;
    WINDOW *msgs;

    int yMax , xMax;
    getmaxyx(stdscr , yMax , xMax);

    if (yMax < 30 || xMax < 25)
    {
        mvprintw(yMax/2 , xMax/2 - strlen("Your window is too small!")/2 , "Your window is too small!");
        getch();
        endwin();
    }

    

    gameWin = newwin(22 , 22 , 4 , 3);
    scoreWin = newwin(3 , 22 , 1 , 3);
    msgs = newwin(3 , 50 , 27 , 3);

    box(gameWin , 0 , 0);
    box(scoreWin , 0 , 0);

    refresh();
    wrefresh(msgs);
    wrefresh(gameWin);
    wrefresh(scoreWin);

    snake *asnake;
    asnake = init_snake(20 , 20);
    Draw(gameWin , asnake , 22 , 22);
    wrefresh(gameWin);
    drawScore(scoreWin);

    int i = 0;
    while (1)
    {
        i = Trigger(gameWin , scoreWin , asnake);
        Draw(gameWin , asnake , 22 , 22);
        if (i == -1 || i == -2)
        {
            break;
        }
        
    }
    mvwprintw(msgs  , 0 , 0, "You dead (%d), press Q to quit" , i);
    wrefresh(msgs);
    while (getch() != 'q')
    {}
    free(asnake);
    
    endwin();
}
