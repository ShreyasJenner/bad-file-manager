#include <menu.h>

#include "store_item_values.h"

void store_item_values(ITEM **my_items, int argc, char **argv, char store[][4]) {
    int i;
    for(i=0;i<argc;i++)  {
        sprintf(store[i],"%d",i+1);
        my_items[i] = new_item(store[i], &argv[i][1]);
    }
    my_items[argc] = (ITEM *)NULL;
}
