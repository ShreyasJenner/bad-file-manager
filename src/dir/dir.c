#include "dir/dir.h"
#include "dir/structs.h"
#include "log.h"
#include "stdheader.h"

/* Function to change directory */
int move_directory(char *dirpath) {
  if (chdir(dirpath) == -1) {
    logerror(__func__, "Error changing directory");
    return -1;
  }
  return 0;
}

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
    if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
      count++;
    }
    entry = readdir(dir);
  }

  /* close dir stream */
  closedir(dir);

  return count;
}

/* Function stores the absolute path of the passed filename
 * Space is allocated as necessary for the path and a pointer is returned to the
 * created char array */
char *store_absolute_path(char *filename) {
  /* Declaration */
  char *abspath;
  char cwd[FILE_SZ];

  /* store the current working directory in a temporary buffer */
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    logerror(__func__, "Error in getcwd");
    return NULL;
  }

  /* if parent directory is / */
  if (!strcmp(cwd, "/")) {
    abspath = (char *)malloc(strlen(filename) + 2);
  } else {
    /* +2 for '/' and '\0' */
    abspath = (char *)malloc(strlen(filename) + strlen(cwd) + 2);
  }
  if (abspath == NULL) {
    logerror(__func__, "Error mallocing space for storing file name");
    return NULL;
  }

  /* copy the filename if filename parent is / */
  if (!strcmp(cwd, "/")) {
    snprintf(abspath, strlen(filename) + 2, "/%s", filename);
  } else {
    /* create the absolute path string */
    snprintf(abspath, strlen(filename) + strlen(cwd) + 2, "%s/%s", cwd,
             filename);
  }

  return abspath;
}

/* Function to get the parent directory of the passed file absolute path */
char *get_parent_dir_absolute_path(char *path) {
  /* Declaration */
  char *pardir;
  int last_idx;

  /* get last occurence of '/' */
  last_idx = strrchr(path, '/') - path;

  /* create string containing only parent path  and return it */
  pardir = malloc(last_idx == 0 ? last_idx + 2 : last_idx + 1);
  if (pardir == NULL) {
    perror("malloc: ");
    logerror(__func__, "Error allocating space for pardir -> malloc");
    return NULL;
  }

  /* ternary operator to handle root directory */
  strncpy(pardir, path, last_idx == 0 ? last_idx + 1 : last_idx);
  pardir[last_idx] = '\0';

  return pardir;
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
  if (data == NULL) {
    logerror(__func__, "Error mallocing space for dir_data");
    return NULL;
  }

  /* allocate space for parent directory and store value in it */
  data->parent_dir = get_parent_dir_absolute_path(dirname);
  if (data->parent_dir == NULL) {
    logerror(__func__, "Error -> get_parent_dir_absolute_path");
    return NULL;
  }

  /* get file count and allocate space */
  data->count = file_count(dirname);
  if (data->count == -1) {
    logerror(__func__, "Error: file_count");
    return NULL;
  }
  data->list = (struct files **)calloc(data->count, sizeof(struct files *));
  if (data->list == NULL) {
    logerror(__func__, "Error callocing space for files list");
    free(data);
    return NULL;
  }

  /* loop to read dir stream from start */
  rewinddir(dir);
  entry = readdir(dir);

  i = 0;
  while (entry != NULL) {
    /* check if entry is current directory */
    if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {

      /* store file type and name in struct */
      data->list[i] = (struct files *)malloc(sizeof(struct files));
      if (data->list[i] == NULL) {
        logerror(__func__, "Error mallocing space for files list item");
        free(data);
        return NULL;
      }

      /* store selected file absolute path */
      data->list[i]->absname = store_absolute_path(entry->d_name);
      if (data->list[i]->absname == NULL) {
        logerror(__func__, "Error -> store_absolute_path");
        return NULL;
      }

      /* store selected file name */
      data->list[i]->relname = malloc(strlen(entry->d_name) + 1);
      if (data->list[i]->relname == NULL) {
        logerror(__func__, "Error mallocing space for rel_name");
        return NULL;
      }
      strcpy(data->list[i]->relname, entry->d_name);

      /* set file type */
      switch (entry->d_type) {
      case DT_BLK:
        strcpy(data->list[i]->type, "BLK");
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

      /* go to next entry */
      i++;
    }
    entry = readdir(dir);
  }

  /* close dir stream */
  closedir(dir);

  return data;
}

/* Function to check if selected file is a directory
 * Absolute file path is passed to it as a string
 * Returns 1 if it is a directory */
int dir_check(char *path) {
  /* Declaration */
  struct stat path_stat;

  /* check if passed absolute path is a directory */
  stat(path, &path_stat);

  return S_ISDIR(path_stat.st_mode);
}

/* Function to change directory and repopulate struct entries */
struct dir_data *change_directory(struct dir_data *data, int idx) {

  /* Declaration */
  char selfile[strlen(data->list[idx]->absname)];

  /* Initialization */
  strcpy(selfile, data->list[idx]->absname);

  /* change working dir */
  if (move_directory(selfile) != 0) {
    logerror(__func__, "Error -> move_directory");
    return NULL;
  }

  /* repopulate list */
  free_dir(data);
  data = get_directory_entries(selfile);
  if (data == NULL) {
    logerror(__func__, "Error: get_directory_entries");
  }

  return data;
}

/* function to free struct containing file list */
void free_dir(struct dir_data *data) {
  /* Declaration */
  int i;

  /* free struct of file list */
  for (i = 0; i < data->count; i++) {
    free(data->list[i]->absname);
    free(data->list[i]->relname);
    free(data->list[i]);
  }
  free(data->parent_dir);
  free(data->list);
  free(data);
}
