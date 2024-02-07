/* STANDARD HEADER FILES */
#include <stdio.h>
#include <form.h>
#include <menu.h>
#include <curses.h>
#include <stdlib.h>
/* STANDARD HEADER FILES */

/* HEADER FILES */
#include "menu_display.h"
#include "print_title.h"
#include "store_item_values.h"
#include "menu_opts_set.h"
#include "dynamic_file_indicator.h"
#include "free_memory.h"
#include "main_loop.h"
/* HEADER FILES */


int min(int a, int b) {
    return a<b?a:b;
}

char* menu_display(int argc, char **argv) {

    /* Declaration */
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *title_win;
    WINDOW *my_menu_win, *my_menu_sub_win;

    WINDOW *form_win, *form_sub_win;
    FIELD **field;
    FORM *form;

    FILE *tty;
    SCREEN *screen;

    char *name=".";
    char store[argc][4];
    char search;
    int c,i,j,end;
    int nlines,ncols,startx,starty;
    int title_win_height, title_win_width;
    int menu_win_height, menu_win_width;
    int menu_sub_win_height, menu_sub_win_width;
    int menu_format_row, menu_format_col;
    int form_win_height, form_win_width;
    int form_sub_win_height, form_sub_win_width;
    /* Declaration */


    /* Initialize curses */
    tty = fopen("/dev/tty", "r+");
    screen = newterm(NULL, tty, tty);
    set_term(screen);
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    /* Initialize curses */

    /* Initialize Variables */
    getmaxyx(stdscr, nlines, ncols);
    starty = 0;
    startx = 0;
    title_win_height = 3;
    title_win_width = ncols;
    menu_win_height = nlines-6;
    menu_win_width = ncols;
    menu_sub_win_height = menu_win_height-1;
    menu_sub_win_width = ncols-10;
    menu_format_row = menu_sub_win_height-1;
    menu_format_col = 1;
    form_win_height = 3;
    form_win_width = ncols;
    form_sub_win_height = form_win_height-1;
    form_sub_win_width = form_win_width-1;
    /* Initialize Variables */

    /* Create Menu Items and Menu */
    my_items = (ITEM **)calloc(argc+1, sizeof(ITEM *));
    store_item_values(my_items, argc, argv, store);
    my_menu = new_menu((ITEM**)my_items);
    /* Create Menu Items and Menu */

    /* Create windows */
    title_win = newwin(title_win_height, title_win_width, starty, startx);
    my_menu_win = newwin(menu_win_height, menu_win_width, starty+3, startx);
    my_menu_sub_win = derwin(my_menu_win,menu_sub_win_height, menu_sub_win_width,starty+1,startx+3);
    /* Create windows */
    
    /* Set menu options and connect to windows */
    menu_opts_set(my_menu, my_menu_win, my_menu_sub_win, menu_format_row, menu_format_col);
    /* Set menu options and connect to windows */


    
    /* Create Form */
    form_win = newwin(form_win_height, form_win_width, nlines-3,startx);
    form_sub_win = derwin(form_win, form_sub_win_height, form_sub_win_width, starty+1,startx+1);
    field = (FIELD **)calloc(2,sizeof(FIELD *));
    field[0] = new_field(1,ncols/2,4,18,0,0);
    field[1] = NULL;
    move_field(field[0],nlines-2,startx+1);
    /* Create Form */

    /* Form options */
    set_field_back(field[0], A_UNDERLINE);
    form = new_form(field);

    //set_form_win(form,form_win);
    //set_form_win(form,form_sub_win);
    /* Form options */

    post_form(form);
    wrefresh(form_win);

    /* Print border around main window; add title */
    print_title(title_win, 1, startx, ncols, "File Manager", COLOR_PAIR(1));
    box(my_menu_win, 0, 0);
    //box(form_win, 0, 0);
    /* Print border around main window; add title */
    
    /* Render */ 
    end = min(argc,menu_format_row);
    dynamic_file_indicator(my_menu_win, 0, end, argv);

    post_menu(my_menu);
    wrefresh(title_win);
    wrefresh(my_menu_win);
    /* Render */ 


    /* Main Loop */
    c = 'a';
    while(c != 'q') {
        int start = top_row(my_menu);
        dynamic_file_indicator(my_menu_win, start, end, argv);
        wrefresh(my_menu_win);
        c = getch();
        if(c=='/') {
            curs_set(1);
            while(c!=10) {
                c = getch();
                //mvwprintw(title_win, 1,1 , "%c", c);
                wrefresh(title_win);
                if(c==KEY_BACKSPACE)
                    form_driver(form, REQ_DEL_PREV);
                else
                    form_driver(form, c);
                wrefresh(form_win);
            }
            curs_set(0);
        }
        else
            name = main_loop(my_menu,form,form_win, &c);
    }
    /* Main Loop */
  
    
    
    /* Free memory */
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    free_field(field[1]);
    free_memory(my_menu, title_win, my_menu_win, my_menu_sub_win, my_items, screen,  tty, argc);
    /* Free memory */

    return name;
}

