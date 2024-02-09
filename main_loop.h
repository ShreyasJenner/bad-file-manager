#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H 

#include <menu.h> 
#include <form.h>

char* main_loop(WINDOW *menu_win, WINDOW *title_win, MENU *menu, ITEM **items, FORM *form, WINDOW *form_win, FIELD **field, int* c, int argc, char **argv, int nlines, int startx, int ncols);

#endif
