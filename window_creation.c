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
#include "window_creation.h"
// HEADER FILES //

void window_creation(int ncols, int nlines, int startx, int starty, WINDOW **title_win, WINDOW **my_menu_win) {
    *title_win = newwin(2, ncols, starty, startx);

    my_menu_win[0] = newwin(30,ncols/3,starty+3,startx);
    my_menu_win[1] = newwin(30,ncols/3,starty+3,startx+(ncols/3));
    my_menu_win[2] = newwin(30,ncols/3,starty+3,3*startx+(2*ncols/3));
}
