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
// HEADER FILES //

void menu_destruction(int argc, MENU *my_menu,ITEM **my_items) {
    int i;

    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i=0;i<argc;i++)
        free_item(my_items[i]);
}
