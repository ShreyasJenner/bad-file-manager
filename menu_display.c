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
#include "window_creation.h"
// HEADER FILES //

void menu_display(int argc, char *argv[]) {
    // Declaration //
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win[3], *title_win;
    PANEL *my_panels[3];
    
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
    my_items[argc] = (ITEM *)NULL;
    
    my_menu = new_menu((ITEM**)my_items);
    // Create Menu Items and Menu //

    
    // Create windows and panels //
    getmaxyx(stdscr, nlines, ncols);
    window_creation(ncols, nlines, startx, starty, &title_win, my_menu_win);
    for(i=0;i<3;i++)
        my_panels[i] = new_panel(my_menu_win[i]);
    // Create windows and panels //


    // sets menu main and sub windows ; sets menu mark//
    set_menu(my_menu, my_menu_win[0],ncols);
    // sets menu main and sub windows ; sets menu mark//
     
  
    // Print border around main window; add title//
    print_title(title_win, 1, startx, ncols, "File Manager", COLOR_PAIR(1));
    mvwprintw(title_win, 0, 0, "%d %d", nlines, ncols);
    
    for(i=0;i<3;i++)
        box(my_menu_win[i], 0, 0);
    // Print border around main window and title //
   
    
    // Render //
    render(title_win, my_panels, my_menu);
    // Render //


    /* Main Loop */
    while((c=getch()) != 'q') {
        ITEM *cur_item = current_item(my_menu);
        switch(c) {
            case KEY_RESIZE:
            {
                WINDOW *old_title = title_win;
                WINDOW **old_menu_win = my_menu_win;
                getmaxyx(stdscr, ncols, nlines);
                window_creation(ncols, nlines, startx, starty, &title_win, my_menu_win);
                for(i=0;i<3;i++)
                    replace_panel(my_panels[i],my_menu_win[i]);
                render(title_win, my_panels, my_menu);
                window_destruction(old_menu_win, old_title);
                break;
            }

            case 'j':
                if(cur_item == my_items[argc-2])
                    menu_driver(my_menu, REQ_FIRST_ITEM);
                else
                    menu_driver(my_menu, REQ_DOWN_ITEM);
                break;

            case 'k':
                if(cur_item == my_items[0])
                    menu_driver(my_menu, REQ_LAST_ITEM);
                else
                    menu_driver(my_menu, REQ_UP_ITEM);
                break;

            case 'l':
                cur_win_index++;
                cur_win_index %= 3;
                break;

            case 'h':
                cur_win_index = (cur_win_index-1+3)%3;
                break;
            
            case KEY_NPAGE:
                menu_driver(my_menu, REQ_SCR_DPAGE);
                break;

            case KEY_PPAGE:
                menu_driver(my_menu, REQ_SCR_UPAGE);
                break;
        }
        wrefresh(my_menu_win[0]);
    }
    /* Main Loop */
   
    
    // Free memory //
    menu_destruction(argc, my_menu, my_items);
    window_destruction(my_menu_win,title_win);
    // Free memory //

    endwin();

}
