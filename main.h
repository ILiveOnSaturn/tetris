//
// Created by iliveonsaturn on 4/10/23.
//

#ifndef TETRIS_MAIN_H
#define TETRIS_MAIN_H

int main();
void end_game(const char* reason);
void clear_grid();
void setup();
void draw_grid(unsigned short animation);
void loop();
void get_bag(short* bag);

#endif //TETRIS_MAIN_H
