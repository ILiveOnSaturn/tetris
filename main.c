#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include "main.h"
#include "parts.h"

#define WIDTH 10 //note that the width should be twice of the normal console grid because of squares.
#define HEIGHT 20
#define BLOCK ██
#define GRID_FILE_NAME "grid.txt"

unsigned short grid[WIDTH][HEIGHT] = {0};

int main() {
    init();
    draw_grid(1);
    loop();
    end_game("");
    return 0;
}

void init() {
    setlocale(LC_ALL, "");
    initscr();
    raw();
    keypad(stdscr, 1);
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    clear_grid();
}

void clear_grid() {
    for (int i=0; i<WIDTH; i++) {
        for (int j=0; j<HEIGHT; j++) {
            grid[i][j] = 0;
        }
    }
}

void loop() {

}

void end_game(const char* reason) {
    if (reason != NULL) {
        printw("%s", reason);
        getch();
    }
    endwin();
}

void draw_grid(unsigned short animation) {
    FILE* ptr;
    char ch;
    ptr = fopen(GRID_FILE_NAME, "r");
    if (NULL == ptr) {
        end_game("File not found");
    }
    ch = fgetc(ptr);
    while (!feof(ptr)) {
        printw("%c", ch);
        if (animation) {
            refresh();
        }
        ch = fgetc(ptr);
    }
    refresh();
    fclose(ptr);
}


