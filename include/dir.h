#ifndef DIR_H
#define DIR_H

#include "structs.h"

int file_count(char *dirname);

void add_path(char *selfile);

struct dir_data *get_directory_entries(char *dirname);

struct dir_data *change_directory(char *selfile, struct dir_data *dirs,
                                  int count);

void free_file_list(struct files **list, int file_count);

void free_dir(struct dir_data *data);

#endif // !DIR_H
