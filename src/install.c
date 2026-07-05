#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "search.h"

/* check if command exists */
static int exists(const char *cmd)
{
    char buf[128];
    snprintf(buf, sizeof(buf), "command -v %s >/dev/null 2>&1", cmd);
    return system(buf) == 0;
}

/* run install safely */
int run_install(PackageManager pm, const char *pkg)
{
    char cmd[512];

    const char *prefix = "";

    /* privilege resolver */
    if (exists("pkexec"))
        prefix = "pkexec";
    else if (exists("sudo"))
        prefix = "sudo";
    else if (exists("doas"))
        prefix = "doas";

    if (strcmp(pm.name, "pacman") == 0)
    {
        snprintf(cmd, sizeof(cmd),
                 "%s pacman -S --noconfirm %s",
                 prefix, pkg);
    }
    else if (strcmp(pm.name, "apt") == 0)
    {
        snprintf(cmd, sizeof(cmd),
                 "%s apt install -y %s",
                 prefix, pkg);
    }
    else if (strcmp(pm.name, "dnf") == 0)
    {
        snprintf(cmd, sizeof(cmd),
                 "%s dnf install -y %s",
                 prefix, pkg);
    }
    else
    {
        return -1;
    }

    return system(cmd);
}
