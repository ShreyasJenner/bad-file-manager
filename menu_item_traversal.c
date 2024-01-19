/*
 * program traverses menu items with vim key bindings
 * accepts a menu pointer and window pointer as arguments
 */

// STANDARD HEADER FILES //
#include <menu.h>
#include <curses.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
#include "menu_item_traversal.h"
// HEADER FILES //

void traverse(MENU *my_menu,WINDOW **my_menu_win,ITEM **my_items,int argc) {
    int c,cur_win_index=0;
    while((c=getch()) != 'q') {
        ITEM *cur_item = current_item(my_menu);
        switch(c) {
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
}
