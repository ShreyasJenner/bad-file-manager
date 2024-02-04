
#include "main_loop.h"

char* main_loop(MENU *menu, FORM *form, WINDOW *form_win, int* c) {

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
            while(*c!=10) {
                *c = getch();
                if(*c == KEY_BACKSPACE)
                    form_driver(form, REQ_DEL_PREV);
                else
                    form_driver(form, *c);
                mvwprintw(form_win,1,1,"%c",*c);
            }
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
}
