#include <ncurses.h>

#include "cave.h"
#include "labyrinth.h"
#include "web_server.h"

int main() {
  init_ncurses();

  int mode = 0;
  Labyrinth labyrinth;

  while (1) {
    print_start_menu();

    char ch = getch();
    if (ch == 'q' || ch == 'Q') {
      break;
    }

    mode = ch - '0';
    if (mode == 1) {
      apply_mode1(&labyrinth);
    } else if (mode == 2) {
      apply_mode2(&labyrinth);
    } else if (mode == 3) {
      apply_mode3();
    } else if (mode == 4) {
      apply_mode4(&labyrinth);
    } else if (mode == 5) {
      mvprintw(9, 0, "open http://localhost:8081");
      init_server();
      clear();
    } else {
      mvprintw(9, 0,
               "Invalid mode selected. Press any key to return to the menu.");
      refresh();
      getch();
    }
  }

  end_ncurses();
  return 0;
}
