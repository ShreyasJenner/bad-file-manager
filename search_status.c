#include <menu.h>

void search_status(WINDOW *title_win, int status) {
    int i;

    if(status==0) {
        mvwprintw(title_win,2,2,"%s","Searching");
        for(i=0;i<8;i++) {
            wdelch(title_win);
        }
    } else if(status == 1) {
        move(2,2);
        clrtoeol();
    } else if(status == -1) {
        mvwprintw(title_win,2,2,"%s","Pattern Not Found");
    }
    wrefresh(title_win);
}
