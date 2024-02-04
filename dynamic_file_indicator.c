#include <menu.h>

#include "dynamic_file_indicator.h"

void dynamic_file_indicator(WINDOW *my_menu_win, int start, int end, char **argv) {
    int i,j;

    for(i=start,j=1;j<=end;i++,j++) {
        if(argv[i][0] == 'D')
            wattron(my_menu_win,COLOR_PAIR(2));
        else
            wattron(my_menu_win,COLOR_PAIR(3));

        mvwprintw(my_menu_win,j,1,"%c",argv[i][0]);

        if(argv[i][0] == 'D')
            wattroff(my_menu_win,COLOR_PAIR(2));
        else
            wattroff(my_menu_win,COLOR_PAIR(3));
    }
}
