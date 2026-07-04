#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "install.h"

void install_package(const char *pkg) {
    char cmd[512];

    if (system("which pacman > /dev/null 2>&1") == 0) {
        printf("[INFO]:Package manager detected, using pacman\n");
        snprintf(cmd, sizeof(cmd), "sudo pacman -S %s", pkg);

    } else if (system("which apt > /dev/null 2>&1") == 0) {
        printf("[INFO]:Package manager detected, using apt\n");
        snprintf(cmd, sizeof(cmd), "sudo apt install -y %s", pkg);

    } else if (system("which dnf > /dev/null 2>&1") == 0) {
        printf("[INFO]:Package manager detected, using dnf\n");
        snprintf(cmd, sizeof(cmd), "sudo dnf install -y %s", pkg);

    } else {
        printf("[ERROR]:No supported package manager found. HAULTING...\n");
        return;
    }

    printf("[INFO]:Running: %s\n", cmd);
    system(cmd);
}
