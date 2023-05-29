//
// Created by iliveonsaturn on 4/10/23.
//

#ifndef TETRIS_MAIN_H
#define TETRIS_MAIN_H

typedef struct {
	short** shape;
	int width;
} Tetrimino;

int main();
void end_game(const char* reason);
void clear_grid();
void setup();
void draw_grid(unsigned short animation);
void draw_part(short n, int x_print, int y_print);
void draw_three_next(short* next);
void loop();
void get_bag(short* bag);
void draw_grid_inside();
void draw_current(Tetrimino* curr, int col, int row);

#endif //TETRIS_MAIN_H
