#include "dir/dir.h"
#include "dir/structs.h"
#include "log.h"
#include "stdheader.h"
#include "tui/tui.h"
#include <curses.h>
#include <string.h>

/* Driver Code */
int main(int argc, char **argv) {
  /* check for file args */
  if (argc < 2) {
    logerror(__func__, "Missing file argument");
    exit(1);
  }

  // NOTE: tui code
  //
  /* Declaration */
  int i;
  struct dir_data *data;
  char selected_item[FILE_SZ];
  MENU *menu;

  /* Initialization */
  strcpy(selected_item, argv[1]);

  /* initialize tui */
  tui_init();

  while (1) {
    fprintf(stderr, "Selected items: %s\n", selected_item);
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

    /* pause */
    i = traverse_menu(menu, selected_item);
    if (strcmp(data->list[i]->type, "DIR")) {
      strcpy(selected_item, "q");
    }
    fprintf(stderr, "Selected items: %s\n", selected_item);
    /* break if quit */

    /* reload menu and directory entries */
    free_dir(data);
    if (destroy_menu(menu) != 0) {
      logerror(__func__, "Error -> destroy_menu");
      exit(1);
    }

    if (!strcmp(selected_item, "q"))
      break;
  }

  /* clean resources */
  tui_deinit();

  // NOTE: dir code
  //
  ///* Check for file arguments */
  // if (argc < 2) {
  //   logerror(__func__, "Missing file argument");
  //   exit(1);
  // }

  ///* change working directory */
  // if (move_directory(argv[1]) != 0) {
  //   logerror(__func__, "Error -> move_directory");
  //   exit(1);
  // }

  ///* Declaration */
  // int i;
  // struct dir_data *data;

  ///* Initialization */
  // data = get_directory_entries(argv[1]);
  // if (data == NULL) {
  //   logerror(__func__, "Error: get_directory_entries");
  //   exit(1);
  // }

  ///* print the directory entries */
  // for (i = 0; i < data->count; i++) {
  //   printf("%d %s %s\n", i, data->list[i]->type, data->list[i]->name);
  // }

  ///* loop to traverse directories */
  // printf("Selected file: %s\n", argv[1]);
  // while (1) {
  //   /* choose a file name and append path to that dir */
  //   scanf("%d", &i);
  //   if (i == -1) {
  //     printf("Quitting\n");
  //     break;
  //   }

  //  printf("Selected file:%s\n", data->list[i]->name);
  //  /* check if selected file is a directory */
  //  if (dir_check(data, i) == 0) {
  //    /* get new directory entries */
  //    data = change_directory(data, i);
  //    if (data == NULL) {
  //      logerror(__func__, "Error: change_directory");
  //      exit(1);
  //    }

  //    /* print the directory entries */
  //    for (i = 0; i < data->count; i++) {
  //      printf("%d %s %s\n", i, data->list[i]->type, data->list[i]->name);
  //    }
  //  }
  //}

  // free_dir(data);

  return 0;
}
