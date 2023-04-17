#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "parts.h"

#define WIDTH 10 //note that the width should be twice of the normal console grid because of squares.
#define HEIGHT 20
#define BLOCK ██
#define GRID_FILE_NAME "grid.txt"
#define MAX_PARTS 7

unsigned short grid[WIDTH][HEIGHT] = {0};

int main() {
    setup();
    draw_grid(1);
    loop();
    end_game("");
    return 0;
}

void setup() {
    srand(time(NULL));
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
    bool running = TRUE;
    short bag[MAX_PARTS];
    get_bag(bag);
    short three_next[3];
    for (int i=0; i<2; i++) {
        three_next[i] = bag[i];
    }
    int parts_in_bag = 4;
    while (running) {

    }
}

void get_bag(short* bag) {
    short parts[MAX_PARTS] = {1, 2, 3, 4, 5, 6, 7};
    int part_num = MAX_PARTS;
    int indx;
    for (int i=0; i<MAX_PARTS; i++) {
        indx = rand()%(6-i);
        bag[i] = parts[indx];
        for (int j=indx; j<part_num-1; j++) {
            parts[j] = parts[j+1];
        }
        --part_num;
    }
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


