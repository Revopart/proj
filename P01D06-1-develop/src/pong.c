#include <stdio.h>

void print_score(int first_score, int second_score);
void draw_field(int first_pos, int second_pos, int ball_x, int ball_y);
void start_game(int first_score, int second_score, int first_pos, int second_pos, int ball_x, int ball_y,
                int ball_direction);
int next_x(int ball_x, int ball_direction);
int next_y(int ball_y, int ball_direction);

int main() {
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
    char key;
    draw_field(first_pos, second_pos, ball_x, ball_y);
    while (first_score != 21 && second_score != 21) {
        scanf("%c", &key);
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
            } else {
                continue;
            }
        } else if (key != ' ') {
            continue;
        }

        printf("\033[0d\033[2J");
        print_score(first_score, second_score);
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
                printf("=");
            } else if (i >= first_pos && i <= first_pos_end && j == 2) {
                printf("|");
            } else if (i >= second_pos && i <= second_pos_end && j == 77) {
                printf("|");
            } else if (i == ball_y && j == ball_x) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void print_score(int first_score, int second_score) {
    switch (first_score) {
        case 0:
            printf("\033[34C***\n\033[34C* *\n\033[34C* *\n\033[34C* *\n\033[34C***\n");
            break;
        case 1:
            printf("\033[34C** \n\033[34C * \n\033[34C * \n\033[34C * \n\033[34C***\n");
            break;
        case 2:
            printf("\033[34C***\n\033[34C  *\n\033[34C***\n\033[34C*  \n\033[34C***\n");
            break;
        case 3:
            printf("\033[34C***\n\033[34C  *\n\033[34C***\n\033[34C  *\n\033[34C***\n");
            break;
        case 4:
            printf("\033[34C* *\n\033[34C* *\n\033[34C***\n\033[34C  *\n\033[34C  *\n");
            break;
        case 5:
            printf("\033[34C***\n\033[34C*  \n\033[34C***\n\033[34C  *\n\033[34C***\n");
            break;
        case 6:
            printf("\033[34C***\n\033[34C*  \n\033[34C***\n\033[34C* *\n\033[34C***\n");
            break;
        case 7:
            printf("\033[34C***\n\033[34C  *\n\033[34C  *\n\033[34C  *\n\033[34C  *\n");
            break;
        case 8:
            printf("\033[34C***\n\033[34C* *\n\033[34C***\n\033[34C* *\n\033[34C***\n");
            break;
        case 9:
            printf("\033[34C***\n\033[34C* *\n\033[34C***\n\033[34C  *\n\033[34C***\n");
            break;
        case 10:
            printf(
                "\033[28C**  *** \n\033[28C *  * * \n\033[28C *  * *\n\033[28C *  "
                "* *\n\033[28C*** ***\n");
            break;
        case 11:
            printf(
                "\033[28C**  **  \n\033[28C *   *  \n\033[28C *   *  \n\033[28C * "
                "  *  \n\033[28C*** ***\n");
            break;
        case 12:
            printf(
                "\033[28C**  *** \n\033[28C *    * \n\033[28C *  ***\n\033[28C *  "
                "*  \n\033[28C*** ***\n");
            break;
        case 13:
            printf(
                "\033[28C**  *** \n\033[28C *    * \n\033[28C *  ***\n\033[28C *  "
                "  *\n\033[28C*** ***\n");
            break;
        case 14:
            printf(
                "\033[28C**  * * \n\033[28C *  * * \n\033[28C *  ***\n\033[28C *  "
                "  *\n\033[28C***   *\n");
            break;
        case 15:
            printf(
                "\033[28C**  *** \n\033[28C *  *   \n\033[28C *  ***\n\033[28C *  "
                "  *\n\033[28C*** ***\n");
            break;
        case 16:
            printf(
                "\033[28C**  *** \n\033[28C *  *   \n\033[28C *  ***\n\033[28C *  "
                "* *\n\033[28C*** ***\n");
            break;
        case 17:
            printf(
                "\033[28C**  *** \n\033[28C *    * \n\033[28C *    *\n\033[28C *  "
                "  *\n\033[28C***   *\n");
            break;
        case 18:
            printf(
                "\033[28C**  *** \n\033[28C *  * * \n\033[28C *  ***\n\033[28C *  "
                "* *\n\033[28C*** ***\n");
            break;
        case 19:
            printf(
                "\033[28C**  *** \n\033[28C *  * * \n\033[28C *  ***\n\033[28C *  "
                "  *\n\033[28C*** ***\n");
            break;
        case 20:
            printf(
                "\033[28C*** *** \n\033[28C  * * * \n\033[28C*** * *\n\033[28C*   "
                "* *\n\033[28C*** ***\n");
            break;
        case 21:
            printf(
                "\033[28C*** **  \n\033[28C  *  *  \n\033[28C**   *  \n\033[28C*  "
                "  *  \n\033[28C*** ***\n");
            break;
    }
    printf("\033[5A");

    switch (second_score) {
        case 0:
            printf("\033[42C***\n\033[42C* *\n\033[42C* *\n\033[42C* *\n\033[42C***\n");
            break;
        case 1:
            printf("\033[42C** \n\033[42C * \n\033[42C * \n\033[42C * \n\033[42C***\n");
            break;
        case 2:
            printf("\033[42C***\n\033[42C  *\n\033[42C***\n\033[42C*  \n\033[42C***\n");
            break;
        case 3:
            printf("\033[42C***\n\033[42C  *\n\033[42C***\n\033[42C  *\n\033[42C***\n");
            break;
        case 4:
            printf("\033[42C* *\n\033[42C* *\n\033[42C***\n\033[42C  *\n\033[42C  *\n");
            break;
        case 5:
            printf("\033[42C***\n\033[42C*  \n\033[42C***\n\033[42C  *\n\033[42C***\n");
            break;
        case 6:
            printf("\033[42C***\n\033[42C*  \n\033[42C***\n\033[42C* *\n\033[42C***\n");
            break;
        case 7:
            printf("\033[42C***\n\033[42C  *\n\033[42C  *\n\033[42C  *\n\033[42C  *\n");
            break;
        case 8:
            printf("\033[42C***\n\033[42C* *\n\033[42C***\n\033[42C* *\n\033[42C***\n");
            break;
        case 9:
            printf("\033[42C***\n\033[42C* *\n\033[42C***\n\033[42C  *\n\033[42C***\n");
            break;
        case 10:
            printf(
                "\033[42C**  *** \n\033[42C *  * * \n\033[42C *  * *\n\033[42C *  "
                "* *\n\033[42C*** ***\n");
            break;
        case 11:
            printf(
                "\033[42C**  **  \n\033[42C *   *  \n\033[42C *   *  \n\033[42C * "
                "  *  \n\033[42C*** ***\n");
            break;
        case 12:
            printf(
                "\033[42C**  *** \n\033[42C *    * \n\033[42C *  ***\n\033[42C *  "
                "*  \n\033[42C*** ***\n");
            break;
        case 13:
            printf(
                "\033[42C**  *** \n\033[42C *    * \n\033[42C *  ***\n\033[42C *  "
                "  *\n\033[42C*** ***\n");
            break;
        case 14:
            printf(
                "\033[42C**  * * \n\033[42C *  * * \n\033[42C *  ***\n\033[42C *  "
                "  *\n\033[42C***   *\n");
            break;
        case 15:
            printf(
                "\033[42C**  *** \n\033[42C *  *   \n\033[42C *  ***\n\033[42C *  "
                "  *\n\033[42C*** ***\n");
            break;
        case 16:
            printf(
                "\033[42C**  *** \n\033[42C *  *   \n\033[42C *  ***\n\033[42C *  "
                "* *\n\033[42C*** ***\n");
            break;
        case 17:
            printf(
                "\033[42C**  *** \n\033[42C *    * \n\033[42C *    *\n\033[42C *  "
                "  *\n\033[42C***   *\n");
            break;
        case 18:
            printf(
                "\033[42C**  *** \n\033[42C *  * *\n\033[42C *  ***\n\033[42C *  "
                "* *\n\033[42C*** ***\n");
            break;
        case 19:
            printf(
                "\033[42C**  *** \n\033[42C *  * *\n\033[42C *  ***\n\033[42C *   "
                " *\n\033[42C*** ***\n");
            break;
        case 20:
            printf(
                "\033[42C*** *** \n\033[42C  * * * \n\033[42C*** * *\n\033[42C*   "
                "* *\n\033[42C*** ***\n");
            break;
        case 21:
            printf(
                "\033[42C*** **  \n\033[42C  *  *   \n\033[42C**   *  \n\033[42C* "
                "   *  \n\033[42C*** ***\n");
            break;
    }
}
