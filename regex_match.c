#include <regex.h>
#include <string.h>
#include <menu.h>

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

void regex_match(char *str,char **argv, int argc, int start,MENU *menu, WINDOW *menu_win, ITEM **items) {
    char str2[30];
    int value,i=start,c='n',counter;
    regex_t reg;

    trim(str,str2);

    value = regcomp(&reg, str2, 0);

    while(c!=27) {
        switch(c) {
            case 'n':
                i++;
                i %= argc;
                counter=0;
                while((value=regexec(&reg,&argv[i][1],0,NULL,0))==REG_NOMATCH) {
                    counter++;
                    if(counter==argc)
                        return ;
                    i++;
                    i %= argc;
                }
                break;

            /*
            case 'b':
                i--;
                i %= argc;
                counter = 0;
                while((value=regexec(&reg,&argv[i][1],0,NULL,0))==REG_NOMATCH) {
                    counter++;
                    if(counter==argc)
                        return ;
                    i--;
                    i %= argc;
                }
            break;
            */
        }

        set_current_item(menu, items[i]);
        wrefresh(menu_win);
        
        c = getch();
    }
}

