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
// HEADER FILES //

void render(WINDOW *title_win, PANEL **panel, MENU *my_menu) {
    wrefresh(title_win);

    post_menu(my_menu);
    update_panels();
    doupdate();
}
