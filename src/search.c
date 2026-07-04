#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

/* ---------------- scoring ---------------- */

static int score_package(const char *name,
                         const char *desc,
                         const char *query)
{
    size_t qlen = strlen(query);

    if (strcmp(name, query) == 0)
        return 100;

    if (strncmp(name, query, qlen) == 0)
        return 80;

    if (strstr(name, query))
        return 50;

    if (strstr(desc, query))
        return 10;

    return 0;
}

static int compare_packages(const void *a, const void *b)
{
    const Package *pa = a;
    const Package *pb = b;

    if (pa->score != pb->score)
        return pb->score - pa->score;

    return strcmp(pa->name, pb->name);
}

/* ---------------- detect backend ---------------- */

PackageManager detect_pm(void)
{
    FILE *fp;

    if ((fp = popen("which apt-cache", "r"))) {
        if (fgetc(fp) != EOF) {
            pclose(fp);
            return (PackageManager){
                "apt",
                "apt-cache search",
                "apt install",
                "apt show"
            };
        }
        pclose(fp);
    }

    if ((fp = popen("which pacman", "r"))) {
        if (fgetc(fp) != EOF) {
            pclose(fp);
            return (PackageManager){
                "pacman",
                "pacman -Ss",
                "pacman -S",
                "pacman -Si"
            };
        }
        pclose(fp);
    }

    if ((fp = popen("which dnf", "r"))) {
        if (fgetc(fp) != EOF) {
            pclose(fp);
            return (PackageManager){
                "dnf",
                "dnf search",
                "dnf install",
                "dnf info"
            };
        }
        pclose(fp);
    }

    return (PackageManager){
        "unknown",
        "echo search not supported",
        "echo install not supported",
        "echo info not supported"
    };
}

/* ---------------- search ---------------- */

int search_packages(PackageManager pm,
                    const char *query,
                    Package packages[],
                    int max)
{
    char command[256];

    snprintf(command,
             sizeof(command),
             "%s %s",
             pm.search_cmd,
             query);

    FILE *fp = popen(command, "r");
    if (!fp)
        return -1;

    char line[512];
    int count = 0;

    while (fgets(line, sizeof(line), fp) && count < max)
    {
        char *sep = strstr(line, " - ");
        if (!sep)
            continue;

        *sep = '\0';

        char *name = line;
        char *desc = sep + 3;

        desc[strcspn(desc, "\n")] = '\0';

        int score = score_package(name, desc, query);
        if (score == 0)
            continue;

        packages[count].score = score;

        snprintf(packages[count].name,
                 sizeof(packages[count].name),
                 "%s",
                 name);

        snprintf(packages[count].description,
                 sizeof(packages[count].description),
                 "%s",
                 desc);

        memset(packages[count].version, 0, sizeof(packages[count].version));
        memset(packages[count].size, 0, sizeof(packages[count].size));
        memset(packages[count].depends, 0, sizeof(packages[count].depends));

        count++;
    }

    pclose(fp);

    qsort(packages, count, sizeof(Package), compare_packages);

    return count;
}

/* ---------------- package info ---------------- */

void fetch_package_info(PackageManager pm,
                        const char *pkg,
                        Package *out)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "%s %s", pm.info_cmd, pkg);

    FILE *fp = popen(cmd, "r");
    if (!fp)
        return;

    char line[512];

    while (fgets(line, sizeof(line), fp))
    {
        /* apt */
        if (strcmp(pm.name, "apt") == 0)
        {
            if (strstr(line, "Version:"))
                snprintf(out->version, sizeof(out->version), "%s", line + 9);

            if (strstr(line, "Installed-Size:"))
                snprintf(out->size, sizeof(out->size), "%s", line + 16);

            if (strstr(line, "Depends:"))
                snprintf(out->depends, sizeof(out->depends), "%s", line + 9);
        }

        /* pacman */
        if (strcmp(pm.name, "pacman") == 0)
        {
            if (strstr(line, "Version"))
                snprintf(out->version, sizeof(out->version), "%s", strchr(line, ':') + 2);

            if (strstr(line, "Installed Size"))
                snprintf(out->size, sizeof(out->size), "%s", strchr(line, ':') + 2);

            if (strstr(line, "Depends On"))
                snprintf(out->depends, sizeof(out->depends), "%s", strchr(line, ':') + 2);
        }

        /* dnf */
        if (strcmp(pm.name, "dnf") == 0)
        {
            if (strstr(line, "Version"))
                snprintf(out->version, sizeof(out->version), "%s", strchr(line, ':') + 2);

            if (strstr(line, "Size"))
                snprintf(out->size, sizeof(out->size), "%s", strchr(line, ':') + 2);

            if (strstr(line, "Requires"))
                snprintf(out->depends, sizeof(out->depends), "%s", strchr(line, ':') + 2);
        }
    }

    pclose(fp);
}
