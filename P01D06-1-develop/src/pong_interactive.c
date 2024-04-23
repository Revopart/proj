#include <ncurses.h>
#include <stdio.h>

void print_score(int score, int player_number);
void draw_field(int first_pos, int second_pos, int ball_x, int ball_y);
void start_game(int first_score, int second_score, int first_pos, int second_pos, int ball_x, int ball_y,
                int ball_direction);
int next_x(int ball_x, int ball_direction);
int next_y(int ball_y, int ball_direction);

int main() {
    initscr();
    noecho();
    int first_score = 0;
    int second_score = 0;
    int first_pos = 11;
    int second_pos = 11;
    int ball_x = 40;
    int ball_y = 13;
    int ball_direction = 1;
    start_game(first_score, second_score, first_pos, second_pos, ball_x, ball_y, ball_direction);
    return 0;
}

void start_game(int first_score, int second_score, int first_pos, int second_pos, int ball_x, int ball_y,
                int ball_direction) {
    clear();
    draw_field(first_pos, second_pos, ball_x, ball_y);
    while (first_score != 21 && second_score != 21) {
        timeout(100);
        char key = getch();
        timeout(-1);

        if (key == 'a') {
            if (first_pos > 1) {
                first_pos--;
            } else {
                continue;
            }
        } else if (key == 'z') {
            if (first_pos < 21) {
                first_pos++;
            } else {
                continue;
            }
        } else if (key == 'k') {
            if (second_pos > 1) {
                second_pos--;
            } else {
                continue;
            }
        } else if (key == 'm') {
            if (second_pos < 21) {
                second_pos++;
            }
        }

        clear();
        print_score(first_score, 1);
        print_score(second_score, 2);
        draw_field(first_pos, second_pos, ball_x, ball_y);
        int first_pos_end = first_pos + 2;
        int second_pos_end = second_pos + 2;
        if (ball_y == 1) {
            ball_y++;
            if (ball_direction == 1) {
                ball_direction = 2;
            } else {
                ball_direction = 3;
            }
            ball_x = next_x(ball_x, ball_direction);
        } else if (ball_y == 23) {
            ball_y--;
            if (ball_direction == 2) {
                ball_direction = 1;
            } else {
                ball_direction = 4;
            }
            ball_x = next_x(ball_x, ball_direction);
        }

        else if (ball_x == 3) {
            if (ball_y >= first_pos && ball_y <= first_pos_end) {
                if (ball_direction == 4) {
                    ball_direction = 1;

                } else {
                    ball_direction = 2;
                }
                ball_x++;
                ball_y = next_y(ball_y, ball_direction);
            } else {
                second_score++;
                ball_x = 40;
                ball_y = 13;
                ball_direction = 2;
            }
        }

        else if (ball_x == 76) {
            if (ball_y >= second_pos && ball_y <= second_pos_end) {
                if (ball_direction == 2) {
                    ball_direction = 3;
                } else {
                    ball_direction = 4;
                }
                ball_x--;
                ball_y = next_y(ball_y, ball_direction);
            } else {
                first_score++;
                ball_x = 40;
                ball_y = 13;
                ball_direction = 3;
            }
        } else {
            ball_x = next_x(ball_x, ball_direction);
            ball_y = next_y(ball_y, ball_direction);
        }
    }
    endwin();
    if (first_score == 21) {
        printf("Player1 wins");
    } else if (second_score == 21) {
        printf("Player2 wins");
    }
}

int next_x(int ball_x, int ball_direction) {
    switch (ball_direction) {
        case 1:
            ball_x++;
            return ball_x;
            break;
        case 2:
            ball_x++;
            return ball_x;
            break;
        case 3:
            ball_x--;
            return ball_x;
            break;
        case 4:
            ball_x--;
            return ball_x;
            break;
    }
    return -1;
}
int next_y(int ball_y, int ball_direction) {
    switch (ball_direction) {
        case 1:
            ball_y--;
            return ball_y;
            break;
        case 2:
            ball_y++;
            return ball_y;
            break;
        case 3:
            ball_y++;
            return ball_y;
            break;
        case 4:
            ball_y--;
            return ball_y;
            break;
    }
    return -1;
}

void draw_field(int first_pos, int second_pos, int ball_x, int ball_y) {
    int first_pos_end = first_pos + 2;
    int second_pos_end = second_pos + 2;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == 0 || i == 24) {
                printw("=");
            } else if (i >= first_pos && i <= first_pos_end && j == 2) {
                printw("|");
            } else if (i >= second_pos && i <= second_pos_end && j == 77) {
                printw("|");
            } else if (i == ball_y && j == ball_x) {
                printw("@");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}

void print_score(int score, int player_number) {
    int x_pos;
    int step = 1;
    if (player_number == 1) {
        if (score > 9) {
            step = 2;
            x_pos = 28;
        } else {
            x_pos = 34;
        }
    } else {
        x_pos = 42;
        if (score > 9) {
            step = 2;
        }
    }
    int temp_score = score;
    for (int i = 0; i < step; i++) {
        if (i == 0 && score > 9) {
            score = score / 10;
        } else if (i == 1) {
            x_pos = x_pos + 5;
            score = temp_score % 10;
        }

        switch (score) {
            case 0:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "* *\n");
                mvprintw(2, x_pos, "* *\n");
                mvprintw(3, x_pos, "* *\n");
                mvprintw(4, x_pos, "***\n");
                break;
            case 1:
                mvprintw(0, x_pos, "** \n");
                mvprintw(1, x_pos, " * \n");
                mvprintw(2, x_pos, " * \n");
                mvprintw(3, x_pos, " * \n");
                mvprintw(4, x_pos, " * \n");
                break;
            case 2:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "  *\n");
                mvprintw(2, x_pos, " * \n");
                mvprintw(3, x_pos, "*  \n");
                mvprintw(4, x_pos, "***\n");
                break;
            case 3:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "  *\n");
                mvprintw(2, x_pos, "***\n");
                mvprintw(3, x_pos, "  *\n");
                mvprintw(4, x_pos, "***\n");
                break;
            case 4:
                mvprintw(0, x_pos, "* *\n");
                mvprintw(1, x_pos, "* *\n");
                mvprintw(2, x_pos, "***\n");
                mvprintw(3, x_pos, "  *\n");
                mvprintw(4, x_pos, "  *\n");
                break;
            case 5:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "*  \n");
                mvprintw(2, x_pos, "***\n");
                mvprintw(3, x_pos, "  *\n");
                mvprintw(4, x_pos, "***\n");
                break;
            case 6:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "*  \n");
                mvprintw(2, x_pos, "***\n");
                mvprintw(3, x_pos, "* *\n");
                mvprintw(4, x_pos, "***\n");
                break;
            case 7:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "  *\n");
                mvprintw(2, x_pos, " * \n");
                mvprintw(3, x_pos, " * \n");
                mvprintw(4, x_pos, " * \n");
                break;
            case 8:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "* *\n");
                mvprintw(2, x_pos, "***\n");
                mvprintw(3, x_pos, "* *\n");
                mvprintw(4, x_pos, "***\n");
                break;
            case 9:
                mvprintw(0, x_pos, "***\n");
                mvprintw(1, x_pos, "* *\n");
                mvprintw(2, x_pos, "***\n");
                mvprintw(3, x_pos, "  *\n");
                mvprintw(4, x_pos, "***\n");
                break;
        }
    }
}
