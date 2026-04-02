#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "install.h"
#include "ui.h"

int main(int argc, char *argv[]) {

    if (argc > 3){
        printf("Usage: myhelper install <package>\n");
        return 1;
    }

    if (strcmp(argv[1], "install") == 0){
        install_package(argv[2]);
    } 
    else if (strcmp(argv[1], "ui") == 0){
    start_ui();   
    } 
    else{
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}
