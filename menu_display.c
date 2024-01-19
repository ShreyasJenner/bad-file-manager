// STANDARD HEADER FILES //
#include <stdio.h>
#include <menu.h>
#include <curses.h>
#include <panel.h>
#include <stdlib.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
#include "menu_item_traversal.h"
#include "print_title.h"
// HEADER FILES //

void menu_display(int argc, char *argv[]) {
    // Declaration //
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win[3], *title_win;
    PANEL *my_panels[3];
    
    char store[argc-1][4];
    int c,i;
    char search;
    int nlines,ncols,startx,starty;
    // Declaration //

    // Initialize curses //
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    // Initialize curses //

    // Initialize Variables //
    getmaxyx(stdscr, nlines, ncols);
    starty = 0;
    startx = 0;
    // Initialize Variables //


    // Create Menu Items //
    my_items = (ITEM **)calloc(argc, sizeof(ITEM *));
   
    for(i=1;i<argc;i++)  {
        sprintf(store[i-1],"%d",i);
        my_items[i-1] = new_item(store[i-1], argv[i]);
    }
    my_items[argc] = (ITEM *)NULL;
    // Create Menu Items //

    
    // Create Menu //
    my_menu = new_menu((ITEM**)my_items);
    // Create Menu //
   

    // Create windows and panels //
    title_win = newwin(2, ncols, starty, startx);

    my_menu_win[0] = newwin(30,ncols/3,starty+3,startx);
    my_menu_win[1] = newwin(30,ncols/3,starty+3,startx+(ncols/3));
    my_menu_win[2] = newwin(30,ncols/3,starty+3,3*startx+(2*ncols/3));
   
    for(i=0;i<3;i++)
        my_panels[i] = new_panel(my_menu_win[i]);
    // Create windows and panels //


    // sets menu main and sub windows ; sets menu mark//
    set_menu_win(my_menu, my_menu_win[0]);
    set_menu_sub(my_menu, derwin(my_menu_win[0],29,(ncols/3)-2,1,1));
    set_menu_format(my_menu, 21, 1);

    set_menu_mark(my_menu, "*"); // mark strings to show selected items
    // sets menu main and sub windows ; sets menu mark//
     
  
    // Print border around main window; add title//
    print_title(title_win, 1, startx, ncols, "File Manager", COLOR_PAIR(1));
    mvwprintw(title_win, 0, 0, "%d %d", nlines, ncols);
    
    for(i=0;i<3;i++)
        box(my_menu_win[i], 0, 0);
    // Print border around main window and title //
   
    
    // Refresh title window//
    wrefresh(title_win);
    // Refresh title window//


    // Post the menu; refresh panels //
    post_menu(my_menu);
    update_panels();
    doupdate();
    // Post the menu; refresh panels //

    
    // Traverse Menu Items //
    traverse(my_menu, my_menu_win, my_items, argc); 
    // Traverse Menu Items //
   
    
    // Free memory //
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i=0;i<argc;i++)
        free_item(my_items[i]);

    endwin();
    // Free memory //

}
