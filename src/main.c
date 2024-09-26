#include "dir.h"
#include "log.h"
#include "stdheader.h"
#include "structs.h"

int main(int argc, char **argv) {
  /* Check for file arguments */
  if (argc < 2) {
    logerror(__func__, "Missing file argument");
    exit(1);
  }

  /* Declaration */
  int count, i;
  struct dir_data *data;

  /* Initialization */
  count = file_count(argv[1]);
  printf("File count:%d\n", count);

  data = get_directory_entries(argv[1]);
  if (data == NULL) {
    logerror(__func__, "Error: get_directory_entries");
    exit(1);
  }

  for (i = 0; i < data->count; i++) {
    printf("%d %s %s\n", i, data->list[i]->type, data->list[i]->name);
  }

  /* choose a file name and append path to that dir */
  scanf("%d", &i);
  add_path(data->list[i]->name);

  /* change dir entries */
  printf("Selected file:%s\n", data->list[i]->name);
  data = change_directory(data->list[i]->name, data, count);
  if (data == NULL) {
    logerror(__func__, "Error: change_directory");
    exit(1);
  }

  for (i = 0; i < data->count; i++) {
    printf("%d %s %s\n", i, data->list[i]->type, data->list[i]->name);
  }

  free_file_list(data->list, count);
  free_dir(data);

  return 0;
}
