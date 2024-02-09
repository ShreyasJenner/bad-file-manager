#include <regex.h>
#include <string.h>
#include <menu.h>


int regex_match_n(char *str, int argc, char **argv, int start) {
    int value,i=start,counter;
    regex_t reg;
    
    value = regcomp(&reg, str, 0);

    counter=0;
    i %= argc;
    while((value=regexec(&reg,&argv[i][1],0,NULL,0))==REG_NOMATCH) {
        counter++;
        if(counter==argc-1)
            return -1;
        i++;
        if(i>argc-1)
            i=0;
    }
    return i;
}

int regex_match_b(char *str, int argc, char **argv, int start) {
    int value,i=start,counter;
    regex_t reg;

    value = regcomp(&reg, str, 0);

    counter = 0;
    if(i<0)
        i = argc-1;
    while((value=regexec(&reg,&argv[i][1],0,NULL,0))==REG_NOMATCH) {
        counter++;
        if(counter==argc-1)
            return -1;
        i--;
        if(i<0)
            i = argc-1;
    }
    return i;
}
