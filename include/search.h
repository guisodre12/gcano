#ifndef SEARCH_H
#define SEARCH_H

typedef struct {
    const char *name;
    const char *search_cmd;
    const char *install_cmd;
    const char *info_cmd;
} PackageManager;

typedef struct {
    char name[128];
    char description[512];
    int score;

    char version[128];
    char size[128];
    char depends[512];
} Package;

PackageManager detect_pm(void);

int search_packages(PackageManager pm,
                    const char *query,
                    Package packages[],
                    int max);

void fetch_package_info(PackageManager pm,
                        const char *pkg,
                        Package *out);

#endif
