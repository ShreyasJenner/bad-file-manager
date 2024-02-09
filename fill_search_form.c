#include <form.h>
#include <menu.h>

void fill_search_form(FORM *form, WINDOW *form_win) {
    int c;
    curs_set(1);
    form_driver(form, REQ_CLR_FIELD);
            while(c!=10) {
                c = getch();
                //mvwprintw(title_win, 1,1 , "%c", c);
                if(c==KEY_BACKSPACE) {
                    form_driver(form, REQ_DEL_PREV);
                }
                else {
                    form_driver(form, c);
                }
                wrefresh(form_win);
            }
    form_driver(form, REQ_VALIDATION);
    curs_set(0);
}
