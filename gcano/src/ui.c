#include <ncurses.h>
#include <string.h>

void start_ui(){
  initscr();
  curs_set(0);
  noecho();
  cbreak();

  keypad(stdscr, TRUE);

  int highlight = 0;
    char *options[] = {
        "Install package",
        "Remove package",
        "Exit"
    };

    int n_options = 3;
    int ch;

    while (1) {
        clear();
        
        mvprintw(0, 55, "Gcano Ain't Not an Organizer!");
        mvprintw(1, 50, "There is no knowledge that is not power");

        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(3 + i, 2, options[i]);
            attroff(A_REVERSE);
        }

        refresh();

        ch = getch();

        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + n_options) % n_options;
                break;

            case KEY_DOWN:
                highlight = (highlight + 1) % n_options;
                break;

            case '\n':
                if(highlight == 0){
                    // Mensagem aparece na tela
    char mesg[]="Digite uma mensagem: ";
    char str[80];

    // para armazenar o número de linhas e o número de colunas da tela
    int row,col;

    // inicia a ncurses
    initscr();

    // obtém o número de linhas e colunas
    getmaxyx(stdscr,row,col);

    // imprime a mensagem no centro da tela
    mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
    getstr(str);
    mvprintw(LINES - 2, 0, "Você digitou: %s", str);
    getch();
    endwin();

                }
                if(highlight == 2){ // Exit
                    endwin();
                    return;
                }
                break;
        }
    }
}
