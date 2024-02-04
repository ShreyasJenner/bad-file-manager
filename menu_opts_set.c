#include "menu_opts_set.h"
#include <menu.h>

void menu_opts_set(MENU *my_menu, WINDOW *my_menu_win, WINDOW *my_menu_sub_win, int row, int col) {
    menu_opts_off(my_menu, O_NONCYCLIC);
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, my_menu_sub_win);

    set_menu_format(my_menu, row, col);
    set_menu_mark(my_menu, "*");
}
