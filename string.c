#include <stdlib.h>
#include <stdio.h>

int main() {
    char buff[20];
    sprintf(buff, "%d", 1);
    printf("%s\n",buff);
    sprintf(buff, "%d", 23);
    printf("%s\n",buff);
}
