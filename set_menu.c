// STANDARD HEADER FILES //
#include <stdio.h>
#include <menu.h>
#include <curses.h>
#include <panel.h>
#include <stdlib.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
#include "print_title.h"
#include "render.h"
#include "menu_destruction.h"
#include "window_destruction.h"
#include "set_menu.h"
// HEADER FILES //

void set_menu(MENU *my_menu, WINDOW *my_menu_win, int ncols) {
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win,29,(ncols/3)-2,1,1));
    set_menu_format(my_menu, 21, 1);

    set_menu_mark(my_menu, "*"); // mark strings to show selected items
}
