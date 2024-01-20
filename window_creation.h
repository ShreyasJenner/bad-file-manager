#ifndef WINDOW_CREATION_H 
#define WINDOW_CREATION_H

#include <curses.h>
#include <menu.h>
#include <panel.h>

void window_creation(int ncols, int nlines, int startx, int starty, WINDOW **title_win, WINDOW **my_menu_win);
#endif
