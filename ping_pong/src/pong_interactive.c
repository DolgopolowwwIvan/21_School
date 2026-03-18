#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define WIN_SCORE 21

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

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    timeout(50);

    while (!game_over) {
        // Очистка экрана
        clear();

        // Верхняя граница
        for (int x = 0; x < WIDTH + 2; x++) {
            printw("-");
        }
        printw("\n");

        // Игровое поле
        for (int y = 0; y < HEIGHT; y++) {
            printw("|");
            for (int x = 0; x < WIDTH; x++) {
                if (x == ball_x && y == ball_y) {
                    printw("*");
                } else if (x == 0 && y >= racket1_y && y < racket1_y + RACKET_SIZE) {
                    printw("|");
                } else if (x == WIDTH - 1 && y >= racket2_y && y < racket2_y + RACKET_SIZE) {
                    printw("|");
                } else {
                    printw(" ");
                }
            }
            printw("|\n");
        }

        // Нижняя граница
        for (int x = 0; x < WIDTH + 2; x++) {
            printw("-");
        }
        printw("\n");

        // Счет
        printf("Player 1: %d\n", score1);
        printf("Player 2: %d\n", score2);

        if (score1 >= WIN_SCORE) {
            printw("\nPlayer 1 wins!\n");
            game_over = 1;
            nodelay(stdscr, FALSE);
            timeout(-1);
        } else if (score2 >= WIN_SCORE) {
            printw("\nPlayer 2 wins!\n");
            game_over = 1;
            nodelay(stdscr, FALSE);
            timeout(-1);
        }

        // Обновление экрана
        refresh();

        // Обработка ввода
        int ch = getch();

        // Управление ракетками
        if (ch == 'a' || ch == 'A') {
            if (racket1_y > 0) racket1_y--;
        }
        if (ch == 'z' || ch == 'Z') {
            if (racket1_y < HEIGHT - RACKET_SIZE) racket1_y++;
        }
        if (ch == 'k' || ch == 'K') {
            if (racket2_y > 0) racket2_y--;
        }
        if (ch == 'm' || ch == 'M') {
            if (racket2_y < HEIGHT - RACKET_SIZE) racket2_y++;
        }

        // Логика мяча
        if (!game_over) {
            if (ball_y == 0 || ball_y == HEIGHT - 1) {
                dir_y = -dir_y;
            }

            if (ball_x == 1) {
                if (ball_y >= racket1_y && ball_y < racket1_y + RACKET_SIZE) {
                    dir_x = -dir_x;
                }
            }

            if (ball_x == WIDTH - 2) {
                if (ball_y >= racket2_y && ball_y < racket2_y + RACKET_SIZE) {
                    dir_x = -dir_x;
                }
            }

            ball_x += dir_x;
            ball_y += dir_y;

            // Проверка гола
            if (ball_x < 0) {
                score2++;
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
                dir_x = 1;
                dir_y = 1;
            }

            if (ball_x >= WIDTH) {
                score1++;
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
                dir_x = -1;
                dir_y = 1;
            }
        }
    }

    if (game_over) {
        getch();
    }

    endwin();
    return 0;
}