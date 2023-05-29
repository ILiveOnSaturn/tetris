#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "main.h"

#define WIDTH 10 //note that the width should be twice of the normal console grid because of squares.
#define HEIGHT 21
#define GRID_OFFSET_COL 13
#define GRID_OFFSET_ROW 2
#define GRID_FILE_NAME "grid.txt"
#define MAX_PARTS 7

char* block = "██";

unsigned short grid[HEIGHT][WIDTH] = {0}; //Top is in row 0
int level = 0;


const Tetrimino parts[MAX_PARTS] = {
        {(short *[]){(short []){1, 1, 0}, (short []){0, 1, 1}, (short []){0, 0, 0}}, 3},         					    	//Z
        {(short *[]){(short []){0, 2, 2}, (short []){2, 2, 0}, (short []){0, 0, 0}}, 3}, 		        			    	//S
        {(short *[]){(short []){3, 3}, (short []){3, 3}}, 2}, 		    							        	        	//O
        {(short *[]){(short []){4, 0, 0}, (short []){4, 4, 4}, (short []){0, 0, 0}}, 3},					             	//J
        {(short *[]){(short []){0, 0, 5}, (short []){5, 5, 5}, (short []){0, 0, 0}}, 3}, 					            	//L
        {(short *[]){(short []){0, 6, 0}, (short []){6, 6, 6}, (short []){0, 0, 0}}, 3}, 			        			    //T
        {(short *[]){(short []){0, 0, 0, 0}, (short []){7, 7, 7, 7}, (short []){0, 0, 0, 0}, (short []){0, 0, 0, 0}}, 4} 	//I
};

int main() {
    setup();
    loop();
    end_game("");
    return 0;
}

void clear_grid() {
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGHT; j++) {
			grid[i][j] = 0;
		}
	}
}

void setup() {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();
    raw();
    keypad(stdscr, 1);
    noecho();
	curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    clear_grid();
}

void copy_tetrimino(Tetrimino* part, int reference) {
	part->width = parts[reference].width;
	part->shape = (short**)malloc(part->width * sizeof(short*));
	for (int i=0; i<part->width; i++) {
		part->shape[i] = (short*)malloc(part->width * sizeof(short*));
		for (int j=0; j<part->width; j++) {
			part->shape[i][j] = parts[reference].shape[i][j];
		}
	}
}

void loop() {
    draw_grid(1);
    bool running = TRUE;
    short bag[MAX_PARTS];
    get_bag(bag);
    short three_next[3];
	Tetrimino current;
	copy_tetrimino(&current, bag[0]-1);
	int col = 5-(current.width - (current.width/2));
	int row = -1;
	for (int i=0; i<3; i++) {
        three_next[i] = bag[i+1];
    }
    int parts_in_bag = 5;
    while (running) {
		if (parts_in_bag == 0) {
			get_bag(bag);
		}
		//draw_part(current-1, col*2+GRID_OFFSET_COL, row+GRID_OFFSET_ROW);
        draw_three_next(three_next);
		draw_grid_inside();
		draw_current(&current, col, row);	
		running = FALSE;
    }
	if (current.shape != NULL) {
		for (int i = 0; i<current.width; i++) {
			free(current.shape[i]);
		}
		free(current.shape);
	}
}

void get_bag(short* bag) {
    short parts[MAX_PARTS];
   	for (int i=0; i<MAX_PARTS; i++) {
		parts[i] = i+1;
	}
	short t;
	int j;
	for (int i=0; i<MAX_PARTS; i++) {
		j = rand()%MAX_PARTS;
		t = parts[i];
		parts[i] = parts[j];
		parts[j] = t;
	}
	for (int i=0; i<MAX_PARTS; i++) {
		bag[i] = parts[i];
	}
}

void end_game(const char* reason) {
    if (reason != NULL) {
        printw("%s", reason);
        refresh();
        getch();
    }
    endwin();
}

void draw_grid_inside() {
	for (int i=0; i<HEIGHT; i++) {
		move(GRID_OFFSET_ROW+i, GRID_OFFSET_COL);
		for (int j=0; j<WIDTH; j++) {
			if (grid[i][j] != 0) {
				attron(COLOR_PAIR(grid[i][j]));
				printw("%s", block);
				attroff(COLOR_PAIR(grid[i][j]));
			} else {
				printw("  ");
			}
		}
	}
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

void draw_current(Tetrimino* curr, int col, int row) {
	for (int i=0; i < curr->width; i++) {
		for (int j=0; j < curr->width; j++) {
			if (curr->shape[i][j] != 0) {
				attron(COLOR_PAIR(curr->shape[i][j]));
				mvprintw(row+i + GRID_OFFSET_ROW, (col+j) * 2 + GRID_OFFSET_COL, "%s", block);
				attroff(COLOR_PAIR(curr->shape[i][j]));	
			}
		}
	}	
}

void draw_part(short n, int x_print, int y_print) {
    attron(COLOR_PAIR(n+1));
    for (int i=0; i<parts[n].width; i++) {
        for (int j=0; j<parts[n].width; j++) {
            refresh();
            if (parts[n].shape[i][j] != 0) {
                mvprintw(y_print + i, x_print + j * 2, "%s", block);
            }
            refresh();
        }
    }
    attroff(COLOR_PAIR(n+1));
    refresh();
}

void draw_three_next(short* next) {
    int col;
    for (int i=0; i<3; i++) { 
		mvprintw(2+i*3, 47, "%d", next[i]);
        col = 40-(parts[next[i]-1].width);
        draw_part(next[i]-1, col, 2+i*3);
    }
}
