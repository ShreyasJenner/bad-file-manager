#ifndef DIR_H
#define DIR_H

#include "structs.h"

int move_directory(char *dirpath);

int file_count(char *dirname);

char *store_absolute_path(char *filename);

struct dir_data *get_directory_entries(char *dirname);

int dir_check(struct dir_data *data, int idx);

struct dir_data *change_directory(struct dir_data *dirs, int idx);

void free_dir(struct dir_data *data);

#endif // !DIR_H
