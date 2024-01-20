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
#include "window_destruction.h"
// HEADER FILES //

void window_destruction(WINDOW **my_menu_win, WINDOW *title_win) {
    for(int i=0;i<3;i++)
        delwin(my_menu_win[i]);
    delwin(title_win);
}
