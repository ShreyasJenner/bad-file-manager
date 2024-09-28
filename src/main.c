#include "dir/dir.h"
#include "dir/structs.h"
#include "log.h"
#include "stdheader.h"
#include "tui/tui.h"

/* Driver Code */
int main(int argc, char **argv) {
  /* check for file args */
  if (argc < 2) {
    logerror(__func__, "Missing file argument");
    exit(1);
  }

  /* Declaration */
  int flag;
  struct dir_data *data;
  char selected_item[FILE_SZ], *selected_item_ptr;
  MENU *menu;

  /* Initialization */
  strcpy(selected_item, argv[1]);
  flag = 1;

  /* initialize tui */
  tui_init();

  /* run the loop till a file that is not a directory is selected */
  while (flag) {
    /* change working directory */
    if (move_directory(selected_item) != 0) {
      logerror(__func__, "Error -> move_directory");
      exit(1);
    }
    /* get the dir data */
    data = get_directory_entries(selected_item);
    if (data == NULL) {
      logerror(__func__, "Error -> get_directory_entries");
      exit(1);
    }

    /* create the menu */
    menu = create_menu(data);
    if (menu == NULL) {
      logerror(__func__, "Error -> create_menu");
      exit(1);
    }

    /* display the menu */
    clear();
    display_menu(menu);

    /* traverse menu */
    selected_item_ptr = traverse_menu(menu, data);

    if (selected_item_ptr == NULL) {
      /* print current directory on quit */
      fprintf(stderr, "DIR\n%s\n", selected_item);
      flag = 0;
    } else if (!dir_check(selected_item_ptr)) {
      /* print selected file */
      fprintf(stderr, "ITEM\n%s\n", selected_item_ptr);
      flag = 0;
    } else {
      /* check if chosen item is a directory */
      strcpy(selected_item, selected_item_ptr);
      // fprintf(stderr, "Dir: %s\n", selected_item);
    }

    /* destroy dir_data and menu */
    free_dir(data);
    if (destroy_menu(menu) != 0) {
      logerror(__func__, "Error -> destroy_menu");
      exit(1);
    }
  }

  /* clean resources */
  tui_deinit();

  return 0;
}
