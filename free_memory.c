#include "free_memory.h"

#include <stdlib.h>
#include <menu.h>

void free_memory(MENU *menu,WINDOW *title_win, WINDOW *menu_win, WINDOW *menu_sub_win, ITEM **items, SCREEN *screen, FILE *tty, int argc) {

    int i;

    unpost_menu(menu);
    free_menu(menu);
    for(i=0;i<argc;i++)
        free_item(items[i]);
    free(items);
    delwin(menu_sub_win);
    delwin(menu_win);
    delwin(title_win);
    delscreen(screen);

    fclose(tty);
}
