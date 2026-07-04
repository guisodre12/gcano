#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "ui.h"
#include "search.h"

/* ---------------- helper ---------------- */

static void print_wrapped(int y, int x, const char *text, int width)
{
    int line = 0, col = 0;

    for (int i = 0; text[i]; i++)
    {
        if (col >= width || text[i] == '\n')
        {
            line++;
            col = 0;
            if (text[i] == '\n') continue;
        }

        mvaddch(y + line, x + col, text[i]);
        col++;
    }
}

/* ---------------- details ---------------- */

void show_details(Package p, PackageManager pm)
{
    int ch, rows, cols;

    while (1)
    {
        clear();
        getmaxyx(stdscr, rows, cols);

        mvprintw(1, 2, "PACKAGE DETAILS");
        mvhline(2, 2, '-', cols - 4);

        mvprintw(4, 2, "Name: %s", p.name);

        mvprintw(6, 2, "Description:");
        print_wrapped(7, 4, p.description, cols - 8);

        int y = 12;
        mvprintw(y++, 2, "Version: %s", p.version[0] ? p.version : "N/A");
        mvprintw(y++, 2, "Size: %s", p.size[0] ? p.size : "N/A");
        mvprintw(y++, 2, "Depends: %s", p.depends[0] ? p.depends : "N/A");

        mvhline(rows - 4, 2, '-', cols - 4);
        mvprintw(rows - 3, 2, "[I] Install   [B] Back");

        refresh();

        ch = getch();

        if (ch == 'b' || ch == 'B')
            return;

        if (ch == 'i' || ch == 'I')
        {
            endwin();
            char cmd[256];
            snprintf(cmd, sizeof(cmd), "%s %s", pm.install_cmd, p.name);
            system(cmd);
            initscr();
        }
    }
}

/* ---------------- results ---------------- */

void show_results(Package packages[], int n, PackageManager pm)
{
    int highlight = 0;
    int offset = 0;
    int ch;

    while (1)
    {
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        int max_visible = rows - 6;

        clear();

        mvprintw(1, 2, "RESULTS (%d)", n);
        mvhline(2, 2, '-', cols - 4);

        for (int i = 0; i < max_visible && (i + offset) < n; i++)
        {
            int idx = i + offset;

            if (idx == highlight) attron(A_REVERSE);

            mvprintw(4 + i, 2, "%-30s | %s",
                     packages[idx].name,
                     packages[idx].description);

            if (idx == highlight) attroff(A_REVERSE);
        }

        mvhline(rows - 2, 2, '-', cols - 4);
        mvprintw(rows - 1, 2, "[ENTER] details  [B] back");

        refresh();

        ch = getch();

        if (ch == KEY_UP)
        {
            if (highlight > 0) highlight--;
            if (highlight < offset) offset--;
        }
        else if (ch == KEY_DOWN)
        {
            if (highlight < n - 1) highlight++;
            if (highlight >= offset + max_visible) offset++;
        }
        else if (ch == '\n')
        {
            show_details(packages[highlight], pm);
        }
        else if (ch == 'b' || ch == 'B')
        {
            return;
        }
    }
}

/* ---------------- main UI ---------------- */

void start_ui()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    PackageManager pm = detect_pm();

    int highlight = 0;
    int ch;

    char input_buf[80];
    memset(input_buf, 0, sizeof(input_buf));

    while (1)
    {
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        clear();

        /* ---------------- BANNER ---------------- */

        const char *title[] = {
" ________  ________  ________  ________   ________            ",
"|\\   ____\\|\\   ____\\|\\   __  \\|\\   ___  \\|\\   __  \\           ",
"| \\  \\___|\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\          ",
" \\ \\  \\  __\\ \\  \\    \\ \\   __  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\         ",
"  \\ \\  \\|\\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\        ",
"   \\ \\_______\\ \\_______\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\       ",
"    \\|_______|\\|_______|\\|__|\\|__|\\|__| \\|__|\\|_______|       ",
"        G C A N O  -  a i n t  n o t  a n  o r g a n i z e r"
        };

        int tsize = 8;
        int start_y = 1;

        for (int i = 0; i < tsize; i++)
        {
            mvprintw(start_y + i,
                     (cols - (int)strlen(title[i])) / 2,
                     "%s",
                     title[i]);
        }

        int banner_end = start_y + tsize;

        /* ---------------- SEARCH BOX ---------------- */

        int box_w = 60;
        int box_x = (cols - box_w) / 2;
        int box_y = banner_end + 2;

        mvprintw(box_y - 1, box_x, "+----------------------------------------------------------+");
        mvprintw(box_y,     box_x, "|                                                          |");
        mvprintw(box_y + 1, box_x, "+----------------------------------------------------------+");

        move(box_y, box_x + 2);
        clrtoeol();

        if (highlight == 0)
            attron(A_REVERSE);

        if (strlen(input_buf) == 0)
            mvprintw(box_y, box_x + 2, "Search packages...");
        else
            mvprintw(box_y, box_x + 2, "%s", input_buf);

        if (highlight == 0)
            attroff(A_REVERSE);

        /* ---------------- EXIT ---------------- */

        if (highlight == 1)
            attron(A_REVERSE);

        mvprintw(rows - 2, 2, "Exit");

        if (highlight == 1)
            attroff(A_REVERSE);

        mvprintw(rows - 1, 2, "Backend: %s", pm.name);

        refresh();

        ch = getch();

        switch (ch)
        {
            case KEY_UP:
            case KEY_DOWN:
                highlight = !highlight;
                break;

            case '\n':
                if (highlight == 0)
                {
                    echo();

                    memset(input_buf, 0, sizeof(input_buf));
                    mvgetnstr(box_y, box_x + 2, input_buf, 80);

                    noecho();

                    Package packages[512];
                    int n = search_packages(pm, input_buf, packages, 512);

                    if (n > 0)
                        show_results(packages, n, pm);
                }
                else
                {
                    endwin();
                    return;
                }
                break;
        }
    }
}
