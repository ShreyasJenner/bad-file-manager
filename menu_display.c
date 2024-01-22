// STANDARD HEADER FILES //
#include <stdio.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
#include "print_title.h"
// HEADER FILES //

void menu_display(int argc, char *argv[]) {
    // Declaration //
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win, *title_win;
    
    char store[argc-1][4];
    int c,i,cur_win_index;
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
    starty = 0;
    startx = 0;
    cur_win_index = 0;
    // Initialize Variables //


    // Create Menu Items and Menu //
    my_items = (ITEM **)calloc(argc, sizeof(ITEM *));
   
    for(i=1;i<argc;i++)  {
        sprintf(store[i-1],"%d",i);
        my_items[i-1] = new_item(store[i-1], argv[i]);
    }
    
    my_menu = new_menu((ITEM**)my_items);
    // Create Menu Items and Menu //

    
    // Create windows //
    getmaxyx(stdscr, nlines, ncols);

    my_menu_win = newwin(10, 20, starty+3, startx);
    title_win = newwin(3, ncols, starty, startx);

    // Create windows //


    // sets menu main and sub windows ; sets menu mark//
    menu_opts_off(my_menu, O_NONCYCLIC);
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win,6,20,1,1));

    set_menu_mark(my_menu, "*");
    // sets menu main and sub windows ; sets menu mark//
     
  
    // Print border around main window; add title//
    print_title(title_win, 1, startx, ncols, "File Manager", COLOR_PAIR(1));
   
    box(my_menu_win, 0, 0);
    // Print border around main window and title //
   
    
    // Render //
    wrefresh(title_win);

    post_menu(my_menu);
    wrefresh(my_menu_win);
    // Render //


    /* Main Loop */
    while((c=getch()) != 'q') {
        ITEM *cur_item = current_item(my_menu);
        switch(c) {
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;

            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                break;

            case 'l':
                menu_driver(my_menu, REQ_RIGHT_ITEM);
                break;

            case 'h':
                menu_driver(my_menu, REQ_LEFT_ITEM);
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
    /* Main Loop */
   
    
    // Free memory //
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i=0;i<argc;i++)
        free_item(my_items[i]);

    // Free memory //

    endwin();

}
