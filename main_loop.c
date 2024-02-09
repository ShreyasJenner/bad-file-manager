#include <menu.h>
#include <string.h>

#include "search_status.h"
#include "main_loop.h"
#include "regex_match.h"
#include "fill_search_form.h"
#include "trim.h"


char* main_loop(WINDOW *menu_win, WINDOW *title_win, MENU *menu, ITEM **items, FORM *form, WINDOW *form_win, FIELD **field, int* c, int argc, char **argv, int nlines, int startx, int ncols) {
    
    int search_index;
    char buff[(ncols/2)+1];
    FILE *pot = fopen("/dev/pts/1","w");

    switch(*c) {
        case 'j':
            menu_driver(menu, REQ_DOWN_ITEM);
            break;

        case 'k':
            menu_driver(menu, REQ_UP_ITEM);
            break;

        case 'l':
            menu_driver(menu, REQ_RIGHT_ITEM);
            break;

        case 'h':
            menu_driver(menu, REQ_LEFT_ITEM);
            break;

        case 'g':
            menu_driver(menu, REQ_FIRST_ITEM);
            break;

        case 'G':
            menu_driver(menu, REQ_LAST_ITEM);
            break;

        case 'a':
            *c = 'q';
            return "a/a";
            break;

        case '/':
            search_status(title_win,0);
            move(nlines-2,startx+1);
            fill_search_form(form, form_win);
            break;

        case 'n':
            strcpy(buff,field_buffer(field[0],0));
            trim(field_buffer(field[0],0),buff);

            search_index = regex_match_n(buff,argc,argv,item_index(current_item(menu))+1);

            if(search_index!=-1) {
                set_current_item(menu, items[search_index]);
                wrefresh(menu_win);
            }
            search_status(title_win, search_index);
            break;

        case 'b':
            strcpy(buff,field_buffer(field[0],0));
            trim(field_buffer(field[0],0),buff);

            search_index = regex_match_b(buff,argc,argv,item_index(current_item(menu))-1);
            if(search_index!=-1) {
                set_current_item(menu, items[search_index]);
                wrefresh(menu_win);
            }
            search_status(title_win, search_index);
            break;

        case 10:
            *c = 'q';
            return (char *)item_description(current_item(menu));
            break;

        case KEY_RESIZE:
            *c = 'q';
            return "1R";
            break;
       
        case KEY_BACKSPACE:
            *c = 'q';
            return "..";
            break;

        default:
            *c = 'q';
            return ".";
            break;
    }
    fclose(pot);
}
