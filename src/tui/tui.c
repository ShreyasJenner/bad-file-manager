#include "tui/tui.h"
#include "dir/dir.h"
#include "dir/structs.h"
#include "log.h"
#include "stdheader.h"

/* Function to initalize curses screen*/
void tui_init() {
  /* handle utf characters */
  setlocale(0, "");
  initscr();
  noecho();
  raw();
  keypad(stdscr, TRUE);

  /* create color pairs */
  // NOTE: use for adding color to menu items
  //  To set color for specific items, manual printing needs to be done of items
  //  instead of using menu update
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
}

/* Function to create a menu where each item is an entry of a directory */
MENU *create_menu(struct dir_data *data) {
  /* Declaration */
  MENU *menu;
  ITEM **items;

  int i;

  /* Allocate space for items */
  items = (ITEM **)calloc(data->count + 1, sizeof(ITEM *));
  if (items == NULL) {
    logerror(__func__, "Error callocing space for items array");
    return NULL;
  }

  /* Create items */
  for (i = 0; i < data->count; i++) {
    items[i] = new_item(data->list[i]->relname, data->list[i]->absname);
    if (items[i] == NULL) {
      perror("new_item: ");
      logerror(__func__, "Error -> new_item");
      return NULL;
    }
  }
  items[i] = NULL;

  /* create menu */
  menu = new_menu(items);
  if (menu == NULL) {
    perror("new_menu: ");
    logerror(__func__, "Error -> new_menu");
    return NULL;
  }

  /* hide menu descriptions  */

  menu_opts_off(menu, O_SHOWDESC);
  return menu;
}

/* Function to destroy the menu and free its items */
int destroy_menu(MENU *menu) {
  /* Declaration */
  int i, count;
  ITEM **items;

  /* Initialization */
  count = item_count(menu);
  items = menu_items(menu);
  if (items == NULL) {
    logerror(__func__, "Error -> menu_items");
    return -1;
  }

  /* unpost the menu */
  if (unpost_menu(menu) != E_OK) {
    perror("unpost_menu: ");
    logerror(__func__, "Error -> unpost_menu");
    return -1;
  }

  /* free the menu */
  if (free_menu(menu) != E_OK) {
    perror("free_menu: ");
    logerror(__func__, "Error -> free_menu");
    return -1;
  }

  /* free the menu items */
  for (i = 0; i < count; i++) {
    int k = free_item(items[i]);
    if (k == E_CONNECTED) {
      fprintf(stderr, "%s: count :%d\n", "Ok alright", i);
    }
    if (k != E_OK) {
      perror("free_item: ");
      logerror(__func__, "Error -> free_item");
      return -1;
    }
  }
  free(items);

  return 0;
}

/* Function to display menu of directory entries */
void display_menu(MENU *menu) {
  /* post the menu*/
  post_menu(menu);
  refresh();
}

/* Function handles menu traversal */
char *traverse_menu(MENU *menu, struct dir_data *data) {
  /* Declaration */
  int ch, flag;

  /* Initialization */
  flag = 1;

  /* loop to read input and traverse menu */
  while (flag) {
    ch = getch();

    switch (ch) {
    /* returns null */
    case 'q':
      flag = 0;
      break;

    case 'j':
      menu_driver(menu, REQ_DOWN_ITEM);
      break;

    case 'k':
      menu_driver(menu, REQ_UP_ITEM);
      break;

    case 'g':
      menu_driver(menu, REQ_FIRST_ITEM);
      break;

    case 'G':
      menu_driver(menu, REQ_LAST_ITEM);
      break;

    /* key code for enter
     * return absolute path of selected file */
    case 10:
      return data->list[item_index(current_item(menu))]->absname;
      break;

    /* key code for backspace
     * return parent dir of file list displayed */
    case KEY_BACKSPACE:
      return data->parent_dir;
      break;
    }

    refresh();
  }

  /* return null if q is pressed */
  return NULL;
}

/* Function to close curses window */
void tui_deinit() { endwin(); }
