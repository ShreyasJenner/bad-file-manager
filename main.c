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

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    for(i=0;i<argc;i++) {
        //printf("i=%d\n",i);
        argv[i] = calloc(1,sizeof(char)*100);
        scanf("%[^\n]%*c",argv[i]);
    }

    /*
    for(i=0;i<argc;i++) {
        printf("%s\n",argv[i]);
    }
    */
   
    char *s = menu_display(argc, argv);

    printf("%s\n",s);

    for(i=0;i<argc;i++) {
        free(argv[i]);
    }
    free(argv);
    return 0;
}
