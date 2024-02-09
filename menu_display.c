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
#include "fill_search_form.h"
#include "regex_match.h"
#include "search_status.h"
/* HEADER FILES */


int min(int a, int b) {
    return a<b?a:b;
}

char* menu_display(int argc, char **argv) {

    /* Declaration */
    ITEM **items;
    MENU *menu;
    WINDOW *title_win;
    WINDOW *menu_win, *menu_sub_win;

    WINDOW *form_win, *form_sub_win;
    FIELD **field;
    FORM *form;

    FILE *tty;
    SCREEN *screen;

    char *name=".", *buff;
    char store[argc][4];
    char search;
    int c,i,j,end,search_index;
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
    search_index = 0;
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
    items = (ITEM **)calloc(argc+1, sizeof(ITEM *));
    store_item_values(items, argc, argv, store);
    menu = new_menu((ITEM**)items);
    /* Create Menu Items and Menu */

    /* Create windows */
    title_win = newwin(title_win_height, title_win_width, starty, startx);
    menu_win = newwin(menu_win_height, menu_win_width, starty+3, startx);
    menu_sub_win = derwin(menu_win,menu_sub_win_height, menu_sub_win_width,starty+1,startx+3);
    /* Create windows */
    
    /* Set menu options and connect to windows */
    menu_opts_set(menu, menu_win, menu_sub_win, menu_format_row, menu_format_col);
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
    box(menu_win, 0, 0);
    //box(form_win, 0, 0);
    /* Print border around main window; add title */
    
    /* Render */ 
    end = min(argc,menu_format_row);
    dynamic_file_indicator(menu_win, 0, end, argv);

    post_menu(menu);
    wrefresh(title_win);
    wrefresh(menu_win);
    /* Render */ 


    /* Main Loop */
    c = 'a';
    while(c != 'q') {
        int start = top_row(menu);
        dynamic_file_indicator(menu_win, start, end, argv);
        wrefresh(menu_win);
        c = getch();
        if(c=='/') {

            search_status(title_win,0);
            move(nlines-2,startx+1);
            fill_search_form(form,form_win);

            search_index = regex_match(field_buffer(field[0],0),argv,argc,item_index(current_item(menu)),menu,menu_win,items);

            search_status(title_win,search_index);
        }
        else {
            name = main_loop(menu,form,form_win, &c);
        }
    }
    /* Main Loop */
  
    
    
    /* Free memory */
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    free_field(field[1]);
    free_memory(menu, title_win, menu_win, menu_sub_win, items, screen,  tty, argc);
    /* Free memory */

    return name;
}

