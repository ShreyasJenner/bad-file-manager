#ifndef MENU_ITEM_TRAVERSAL_H 
#define MENU_ITEM_TRAVERSAL_H

#include <curses.h>
#include <menu.h>
#include <panel.h>

void traverse(MENU *menu, WINDOW **win,ITEM **item, int argc);
#endif
