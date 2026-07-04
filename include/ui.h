#ifndef UI_H
#define UI_H

#include "search.h"

void start_ui(void);

void show_results(Package packages[],
                  int n,
                  PackageManager pm);

void show_details(Package p,
                  PackageManager pm);

#endif
