#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 80

void print_board(int board[ROWS][COLS]);
void read_file(int matrix[ROWS][COLS]);
void copy_matrix(int buffer[ROWS][COLS], int board[ROWS][COLS]);
void button_logic(int *delay_ptr);
void update_cell(int new_board[ROWS][COLS], int board[ROWS][COLS]);
void update_board(int board[ROWS][COLS]);
int neighbors(int i, int j, int board[ROWS][COLS]);

int main() {
    int board[ROWS][COLS];
    int delay = 100000;

    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    read_file(board);

    // Основной игровой цикл
    while (1) {
        clear();
        print_board(board);

        mvprintw(ROWS, 0, "Speed: %d ms (A-faster, Z-slower, SPACE-exit)", delay / 1000);
        refresh();

        button_logic(&delay);

        update_board(board);
    }

    endwin();
    return 0;
}

// Построчно отрисовыем поле, ncurces просто крутит эту функцию в цикле
void print_board(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1) {
                printw("0");  //  Клетка в которой кто-то живет
            } else {
                printw("-");  // Пустая клетка
            }
        }
        printw("\n");
    }
}

void read_file(int matrix[ROWS][COLS]) {
    int seed_number;
    FILE *fp = 0;

    clear();
    printw("Select an option from 1 to 5: ");
    refresh();

    echo();
    timeout(-1);
    seed_number = getch() - '0';

    noecho();
    timeout(0);

    switch (seed_number) {
        case 1:
            fp = fopen("seed1.txt", "r");
            break;
        case 2:
            fp = fopen("seed2.txt", "r");
            break;
        case 3:
            fp = fopen("seed3.txt", "r");
            break;
        case 4:
            fp = fopen("seed4.txt", "r");
            break;
        case 5:
            fp = fopen("seed5.txt", "r");
            break;
        default:
            printf("Select an option from 1 to 5");
            refresh();
            read_file(matrix);
            return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char ch;
            fscanf(fp, " %c", &ch);
            if (ch == '1') {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }

    fclose(fp);
}

void button_logic(int *delay_ptr) {
    int ch = getch();

    if (ch != ERR) {
        if (ch == 'A' || ch == 'a') {
            *delay_ptr -= 10000;
            if (*delay_ptr <= 10000) {
                *delay_ptr = 10000;
            }
        } else if (ch == 'Z' || ch == 'z') {
            *delay_ptr += 10000;
        } else if (ch == ' ') {
            endwin();
            exit(0);
        }
    }

    timeout(*delay_ptr / 1000);
}

void update_cell(int new_board[ROWS][COLS], int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1 &&
                (neighbors(i, j, board) < 2 || neighbors(i, j, board) > 3))  // клетка умирает
                new_board[i][j] = 0;
            else if (board[i][j] == 0 && neighbors(i, j, board) == 3)
                new_board[i][j] = 1;  // в мертвой клетке рождается новая клетка
            else
                new_board[i][j] = board[i][j];
        }
    }
}

void update_board(int board[ROWS][COLS]) {
    int new_board[ROWS][COLS];
    update_cell(new_board, board);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

int neighbors(int i, int j, int board[ROWS][COLS]) {
    int live_neighbors = 0;
    for (int k = -1; k <= 1; k++) {  // подсчет количества живых соседей
        for (int l = -1; l <= 1; l++) {
            if (k == 0 && l == 0) continue;  // пропускаем текущую клетку

            int x = i + k;
            int y = j + l;

            if (x < 0)  // выход за пределы поля
                x = ROWS - 1;
            else if (x >= ROWS)
                x = 0;
            if (y < 0)
                y = COLS - 1;
            else if (y >= COLS)
                y = 0;

            if (x >= 0 && x < ROWS && y >= 0 &&
                y < COLS)  // проверяем, находится ли соседняя клетка внутри поля
                live_neighbors += board[x][y];
        }
    }
    return live_neighbors;
}