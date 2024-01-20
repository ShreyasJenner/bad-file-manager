/*
 * function that prints title of the program
 * it accepts a window as argument where it prints the given text
 */
// STANDARD HEADER FILES //
#include <stdio.h>
#include <menu.h>
#include <curses.h>
#include <string.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
#include "print_title.h"
// HEADER FILES //

void print_title(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {
    int length, x, y;
    float temp;

    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;

    length = strlen(string);
    temp = (width-length)/2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}
