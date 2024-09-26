#include "dir.h"
#include "log.h"
#include "stdheader.h"
#include "structs.h"
#include <string.h>
#include <unistd.h>

/* Function to get file count in directory */
int file_count(char *dirname) {
  /* Declaration */
  DIR *dir;
  struct dirent *entry;
  int count;

  /* Initialization */
  dir = opendir(dirname);
  if (dir == NULL) {
    logerror(__func__, "Error opening directory");
    return -1;
  }
  count = 0;

  /* get file count */
  entry = readdir(dir);
  while (entry != NULL) {
    count++;
    entry = readdir(dir);
  }

  /* close dir stream */
  closedir(dir);

  return count;
}

/* Function to add absolute path to selected string */
void add_path(char *selfile) {
  /* Declaration */
  char temp[FILE_SZ];

  /* Initialization */
  strcpy(temp, selfile);

  getcwd(selfile, 256);
  selfile[strlen(selfile)] = '/';
  strcat(selfile, temp);
}

/* Function to read directory entry and return list of files and directories
 * present
 * Returns a char ** array that stores the file type and file name */
struct dir_data *get_directory_entries(char *dirname) {
  /* Declaration */
  int i;

  DIR *dir;
  struct dirent *entry;
  struct dir_data *data;

  /* open dir stream */
  dir = opendir(dirname);
  if (dir == NULL) {
    logerror(__func__, "Error opening directory stream");
    return NULL;
  }

  /* allocating space for char array */
  data = (struct dir_data *)malloc(sizeof(struct dir_data));

  /* get file count and allocate space */
  data->count = file_count(dirname);
  if (data->count == -1) {
    logerror(__func__, "Error: file_count");
    return NULL;
  }
  data->list = (struct files **)calloc(data->count, sizeof(struct files *));

  /* store current working directory */
  data->cwd = (char *)malloc(FILE_SZ);
  add_path(data->cwd);

  /* loop to read dir stream from start */
  rewinddir(dir);
  entry = readdir(dir);

  i = 0;
  while (entry != NULL) {
    /* store file type and name in struct */
    data->list[i] = (struct files *)malloc(sizeof(struct files));

    /* set file type */
    switch (entry->d_type) {
    case DT_BLK:
      strcpy(data->list[i]->type, "BLOK");
      break;

    case DT_CHR:
      strcpy(data->list[i]->type, "CHAR");
      break;

    case DT_DIR:
      strcpy(data->list[i]->type, "DIR");
      break;

    case DT_FIFO:
      strcpy(data->list[i]->type, "PIPE");
      break;

    case DT_LNK:
      strcpy(data->list[i]->type, "SLNK");
      break;

    case DT_REG:
      strcpy(data->list[i]->type, "REG");
      break;

    case DT_SOCK:
      strcpy(data->list[i]->type, "SOCK");
      break;

    case DT_UNKNOWN:
      strcpy(data->list[i]->type, "UNKO");
      break;
    }

    /* store file name */
    strcpy(data->list[i]->name, entry->d_name);

    /* go to next entry */
    i++;
    entry = readdir(dir);
  }

  /* close dir stream */
  closedir(dir);

  return data;
}

/* Function to change directory and repopulate struct entries */
struct dir_data *change_directory(char *selfile, struct dir_data *data,
                                  int count) {
  /* change working dir */
  if (chdir(selfile) == -1) {
    logerror(__func__, "Error changing directory");
    return NULL;
  }

  /* repopulate list */
  free_file_list(data->list, count);
  data = get_directory_entries(selfile);
  if (data == NULL) {
    logerror(__func__, "Error: get_directory_entries");
  }

  return data;
}

/* function to free struct containing file list */
void free_file_list(struct files **list, int file_count) {
  /* Declaration */
  int i;

  /* free struct of file list */
  for (i = 0; i < file_count; i++) {
    free(list[i]);
  }
  free(list);
}

/* Function to free directory */
void free_dir(struct dir_data *data) { free(data); }
