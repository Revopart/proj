#include "interface.h"

void print_figure(WINDOW *window, int **shapeMatrix, int startY, int startX) {
  for (int row = 0; row < FIGURE_SIZE; row++)
    for (int col = 0; col < FIGURE_SIZE; col++)
      if (shapeMatrix[row][col]) draw_block(window, startY + row, startX + col);
  wrefresh(window);
}

void draw_block(WINDOW *window, int posY, int posX) {
  init_pair(7, 7, 7);
  wattron(window, COLOR_PAIR(7));
  mvwprintw(window, posY + 1, posX * 2 + 1, "  ");
  wattroff(window, COLOR_PAIR(7));
}

void erase_figure(WINDOW *window, int startY, int startX) {
  for (int row = 0; row < FIGURE_SIZE; row++)
    for (int col = 0; col < FIGURE_SIZE; col++)
      remove_block(window, startY + row, startX + col);
  wrefresh(window);
}

void remove_block(WINDOW *window, int posY, int posX) {
  mvwprintw(window, posY + 1, posX * 2 + 1, "  ");
}

void draw_field(WINDOW *window, int **gameField) {
  for (int row = 0; row < FIELD_HEIGHT; row++)
    for (int col = 0; col < FIELD_WIDTH; col++) {
      remove_block(window, row, col);
      if (gameField[row][col]) draw_block(window, row, col);
    }
  wrefresh(window);
}