#ifndef REGEX_MATCH_H
#define REGEX_MATCH_H

void trim(char *str, char *str1);

int regex_match_n(char *str, int argc, char **argv, int start);

int regex_match_b(char *str, int argc, char **argv, int start);
#endif
