/*
 * not yet
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
#include "print_title.h"
// HEADER FILES //


int main() {
    int argc,i;
    scanf("%d",&argc);
    
    char **argv = (char **)(calloc(argc,sizeof(char*)));

    for(i=0;i<argc;i++) {
        argv[i] = calloc(1,sizeof(char)*10);
        scanf("%s",argv[i]);
    }
    char* s = menu_display(argc, argv);

    printf("%s\n",s);
    return 0;
}
