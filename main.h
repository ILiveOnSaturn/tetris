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

extern Tetrimino parts[MAX_PARTS] = {
    {(short**)({(short*){1, 1, 0}, (short*){0, 1, 1}, (short*){0, 0, 0}}), 3},         						//Z
	{(short**)({(short*){0, 2, 2}, (short*){2, 2, 0}, (short*){0, 0, 0}}), 3}, 		        				//S
	{(short**)({(short*){3, 3}, (short*){3, 3}}), 2}, 		    							        		//O
	{(short**){(short*){4, 0, 0}, (short*){4, 4, 4}, (short*){0, 0, 0}}, 3},					        	//J
	{(short**){(short*){0, 0, 5}, (short*){5, 5, 5}, (short*){0, 0, 0}}, 3}, 					        	//L
	{(short**){(short*){0, 6, 0}, (short*){6, 6, 6}, (short*){0, 0, 0}}, 3}, 			        			//T
	{(short**){(short*){0, 0, 0, 0}, (short*){7, 7, 7, 7}, (short*){0, 0, 0, 0}, (short*){0, 0, 0, 0}}, 4} 	//I
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
