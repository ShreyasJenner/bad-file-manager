#ifndef REGEX_MATCH_H
#define REGEX_MATCH_H

void trim(char *str, char *str1);

void regex_match(char *str,char **argv, int argc, int start, MENU *menu, WINDOW *menu_win, ITEM **items);
#endif
