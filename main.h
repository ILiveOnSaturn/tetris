//
// Created by iliveonsaturn on 4/10/23.
//

#ifndef TETRIS_MAIN_H
#define TETRIS_MAIN_H

#define MAX_PARTS 7

typedef struct {
	short** shape;
	int width;
} Tetrimino;

const Tetrimino parts[MAX_PARTS] = {
    {{{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}, 3}, 						//Z
	{{{0, 2, 2}, {2, 2, 0}, {0, 0, 0}}, 3}, 						//S
	{{{3, 3}, {3, 3}}, 2}, 											//O
	{{{4, 0, 0}, {4, 4, 4}, {0, 0, 0}}, 3},							//J
	{{{0, 0, 5}, {5, 5, 5}, {0, 0, 0}}, 3}, 						//L
	{{{0, 6, 0}, {6, 6, 6}, {0, 0, 0}}, 3}, 						//T
	{{{0, 0, 0, 0}, {7, 7, 7, 7}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 4} 	//I
};


int main();
void end_game(const char* reason);
void clear_grid();
void setup();
void draw_grid(unsigned short animation);
void draw_part(short n, int x, int y);
void draw_three_next(short* next);
void loop();
void get_bag(short* bag);

#endif //TETRIS_MAIN_H
