/*
 * main c program
 * calls menu display
 * accepts command line arguments
 */

// STANDARD HEADER FILES //
#include <stdio.h>
#include <stdlib.h>
// STANDARD HEADER FILES //

// HEADER FILES //
#include "menu_display.h"
#include "menu_item_traversal.h"
#include "print_title.h"
// HEADER FILES //


int main(int argc, char *argv[]) {
    menu_display(argc, argv);

    return 0;
}
