#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define WIN_SCORE 1

void window(int racket1_y, int racket2_y, int ball_x, int ball_y, int score1, int score2) {
    // ANSI escape codes для очистки экрана.
    printf("\033[H\033[J");

    // Верхняя граница
    for (int x = 0; x < WIDTH + 2; x++) {
        printf("-");
    }
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|");

        for (int x = 0; x < WIDTH; x++) {
            if (x == ball_x && y == ball_y) {
                printf("*");
            } else if (x == 0 && y >= racket1_y && y < racket1_y + RACKET_SIZE) {
                printf("|");
            } else if (x == WIDTH - 1 && y >= racket2_y && y < racket2_y + RACKET_SIZE) {
                printf("|");
            } else {
                printf(" ");
            }
        }

        printf("|\n");
    }

    // Нижняя граница
    for (int x = 0; x < WIDTH + 2; x++) {
        printf("-");
    }
    printf("\n");

    printf("Player 1: %d\n", score1);
    printf("Player 2: %d\n", score2);
}

int main(void) {
    int racket1_y = (HEIGHT - RACKET_SIZE) / 2;
    int racket2_y = (HEIGHT - RACKET_SIZE) / 2;

    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;

    int dir_x = 1;
    int dir_y = 1;

    int score1 = 0;
    int score2 = 0;

    int game_over = 0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    while (!game_over) {
        window(racket1_y, racket2_y, ball_x, ball_y, score1, score2);

        char key = getchar();

        // Управление первого игрока
        if (key == 'a' || key == 'A') {
            if (racket1_y > 0) {
                racket1_y--;
            }
        } else if (key == 'z' || key == 'Z') {
            if (racket1_y < HEIGHT - RACKET_SIZE) {
                racket1_y++;
            }
        }

        // Управление второго игрока
        if (key == 'k' || key == 'K') {
            if (racket2_y > 0) {
                racket2_y--;
            }
        } else if (key == 'm' || key == 'M') {
            if (racket2_y < HEIGHT - RACKET_SIZE) {
                racket2_y++;
            }
        }

        if (key == ' ') {
        }

        if (ball_y == 0 || ball_y == HEIGHT - 1) {
            dir_y = -dir_y;
        }

        if (ball_x == 1) {
            if (ball_y >= racket1_y && ball_y < racket1_y + RACKET_SIZE) {
                dir_x = -dir_x;
            }
        }

        // Проверка столкновения с правой ракеткой
        if (ball_x == WIDTH - 2) {
            if (ball_y >= racket2_y && ball_y < racket2_y + RACKET_SIZE) {
                dir_x = -dir_x;
            }
        }

        ball_x += dir_x;
        ball_y += dir_y;

        if (ball_x < 0) {
            score2++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            dir_x = 1;
            dir_y = 1;

            if (score2 == WIN_SCORE) {
                window(racket1_y, racket2_y, ball_x, ball_y, score1, score2);
                printf("\nPlayer 1 win!\n");
                game_over = 1;
            }
        }

        if (ball_x >= WIDTH) {
            score1++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            dir_x = -1;
            dir_y = 1;

            if (score1 == WIN_SCORE) {
                window(racket1_y, racket2_y, ball_x, ball_y, score1, score2);
                printf("\nPlayer 2 win!\n");
                game_over = 1;
            }
        }

        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    return 0;
}