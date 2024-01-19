#ifndef PRINT_TITLE_H 
#define PRINT_TITLE_H

#include <curses.h>

void print_title(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
#endif
