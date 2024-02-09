#include "trim.h"

void trim(char *str, char *str1)
{
    int idx = 0, j, k = 0;

    while (str[idx] == ' ')
        idx++;
 
    for (j = idx; str[j] != '\0'; j++) {
        str1[k] = str[j];
        k++;
    }

    while(str1[k-1]==' ')
        k--;

    str1[k] = '\0';
}
