#include <ncurses.h>
#include <stdio.h>

#define ROWS 25
#define COLS 80

int read_matrix(int matrix[ROWS][COLS]);
int count_ncells(int matrix[ROWS][COLS], int row, int col);
int next_generation(int ncells, int status_cell);
int is_end(int matrix[ROWS][COLS]);
void output(int matrix[ROWS][COLS], int status_matrix[ROWS][COLS]);
int change_speed(int speed, char key, int *status);

int main() {
    int matrix[ROWS][COLS];
    int status_matrix[ROWS][COLS];
    int speed = 300;
    int end = 0;
    int status = 1;
    int exit_flag = 0;

    end = read_matrix(matrix);
    if (freopen("/dev/tty", "r", stdin)) {
        initscr();
        nodelay(stdscr, true);
        noecho();

        while (end != 1) {
            clear();
            output(matrix, status_matrix);
            char key = getch();
            timeout(speed);

            speed = change_speed(speed, key, &status);
            if (is_end(matrix) || status == 0) {
                end = 1;
            }
        }
        endwin();
        printf("game finished");
    }
    return exit_flag;
}

int read_matrix(int matrix[ROWS][COLS]) {
    int flag = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                flag = -1;
            }
        }
    }

    return flag;
}

int count_ncells(int matrix[ROWS][COLS], int row, int col) {
    int count = 0;
    int up = row - 1;
    int down = row + 1;
    int left = col - 1;
    int right = col + 1;

    if (up < 0) up = ROWS - 1;
    if (down > ROWS - 1) down = 0;
    if (left < 0) left = COLS - 1;
    if (right > COLS - 1) right = 0;

    count += matrix[up][left];
    count += matrix[up][right];
    count += matrix[down][left];
    count += matrix[down][right];
    count += matrix[up][col];
    count += matrix[down][col];
    count += matrix[row][left];
    count += matrix[row][right];
    return count;
}

int next_generation(int ncells, int status_cell) {
    int next_g = 0;
    if (ncells == 3)
        next_g = 1;
    else if (ncells == 2 && status_cell == 1)
        next_g = 1;
    else
        next_g = 0;
    return next_g;
}

int is_end(int matrix[ROWS][COLS]) {
    int sum = 0;
    int flag = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == 1) {
                sum++;
            }
        }
    }
    if (sum == ROWS * COLS || sum == 0) {
        flag = 1;
    }
    return flag;
}

void output(int matrix[ROWS][COLS], int status_matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int ncells = count_ncells(matrix, i, j);
            status_matrix[i][j] = next_generation(ncells, matrix[i][j]);
            if (status_matrix[i][j] == 1) {
                printw("@");
            } else {
                printw("-");
            }
        }
        printw("\n");
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = status_matrix[i][j];
        }
    }
}

int change_speed(int speed, char key, int *status) {
    switch (key) {
        case 'k':
            speed -= 100;
            break;
        case 'j':
            speed += 100;
            break;
        case 'q':
            *status = 0;
            break;
    }
    if (speed < 0) {
        speed = 0;
    }
    return speed;
}
