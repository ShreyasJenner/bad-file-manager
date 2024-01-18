// STANDARD HEADER FILES //
#include <stdio.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
// HEADER FILES //

// function prints title 
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

void menu_display(int argc, char *argv[]) {
    // Declaration //
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win;
    
    char store[argc-1][4];
    int c,i;
    int nlines,ncols,startx,starty;
    // Declaration //

    // Initialize Variables //
    nlines = 15;
    ncols = 40;
    starty = 5;
    startx = 4;
    // Initialize Variables //

    // Initialize curses //
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    // Initialize curses //

    
    // Create Items //
    my_items = (ITEM **)calloc(argc, sizeof(ITEM *));
   
    for(i=1;i<argc;i++)  {
        sprintf(store[i-1],"%d",i);
        my_items[i-1] = new_item(store[i-1], argv[i]);
    }
    my_items[argc] = (ITEM *)NULL;
    // Create Items //

    
    // Create Menu //
    my_menu = new_menu((ITEM**)my_items);
    // Create Menu //
    
    // Create Window; Set main window and sub window // 
    my_menu_win = newwin(nlines,ncols,starty,startx);
    keypad(my_menu_win,TRUE); //enables function keys

    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win,nlines-4,ncols-2,starty-2,startx-3));
    set_menu_format(my_menu, nlines-4, 1);

    set_menu_mark(my_menu, " * "); // mark strings to show selected items
    // Create Window; Set main window and sub window// 
  

    // Print border around main window and title //
    box(my_menu_win,0,0);
    print_title(my_menu_win, 1, 0, 40, "File Manager", COLOR_PAIR(1));
    mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
    mvwhline(my_menu_win, 2, 1, ACS_HLINE, ncols-2);
    mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
    //mvprintw(3, 0, "F1 to exit");
    refresh();
    // Print border around main window and title //


    // Post the menu //
    post_menu(my_menu);
    wrefresh(my_menu_win);
    // Post the menu //

    
    // Traverse Menu Items //
    while((c=getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;

            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            
            case KEY_NPAGE:
                menu_driver(my_menu, REQ_SCR_DPAGE);
                break;

            case KEY_PPAGE:
                menu_driver(my_menu, REQ_SCR_UPAGE);
                break;
        }
        wrefresh(my_menu_win);
    }
    // Traverse Menu Items //
   
    
    // Free memory //
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i=0;i<argc;i++)
        free_item(my_items[i]);
    endwin();
    // Free memory //

}
