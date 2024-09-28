#ifndef STRUCTS_H
#define STRUCTS_H

#define FILE_SZ 256
#define FILE_TYPE_SZ 5

/*
 * type -> indicates type of file
 *        "BLK" = block
 *        "CHAR" =char
 *        "DIR" = dir
 *        "PIPE" = pipe
 *        "SLNK" = slnk
 *        "REG" = reg
 *        "SOCK" = sock
 * name -> stores absolute path of file
 */
struct files {
  char type[FILE_TYPE_SZ];
  char *absname;
  char *relname;
};

/*
 * list -> list of file entries
 * count -> no of files
 * cwd -> current working directory
 * selected -> selected file by user
 */
struct dir_data {
  struct files **list;
  int count;

  char *parent_dir;
};

#endif // !STRUCTS_H
