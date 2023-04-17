//
// Created by iliveonsaturn on 4/10/23.
//

#ifndef TETRIS_MAIN_H
#define TETRIS_MAIN_H

int main();
void setup();
void end_game(const char* reason);
void draw_grid(unsigned short animation);
void loop();
void clear_grid();
void get_bag(short* bag);

#endif //TETRIS_MAIN_H
