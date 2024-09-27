#ifndef TUI_H
#define TUI_H

#include "dir/structs.h"
#include "stdheader.h"

void tui_init();

MENU *create_menu(struct dir_data *data);

int destroy_menu(MENU *menu);

void display_menu(MENU *menu);

int traverse_menu(MENU *menu, char *selected_item);

void tui_deinit();

#endif // !TUI_H