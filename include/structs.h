#ifndef STRUCTS_H
#define STRUCTS_H

#define FILE_SZ 256
#define FILE_TYPE_SZ 5

struct files {
  char type[FILE_TYPE_SZ];
  char name[FILE_SZ];
};

struct dir_data {
  struct files **list;
  int count;
  char *cwd;
};

#endif // !STRUCTS_H
