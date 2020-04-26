
#pragma once
#include "tetromino.hpp"
#include <SDL.h>

const int width = 10;
const int height = 24;
const int showHeight = 20;

class mainBoard {
public:
    mainBoard();
    void draw(SDL_Renderer *);

    bool collision(const Tetromino &t);
    void unite(const Tetromino &t);
    int getScore() const;
private:
    int score = 0;
    bool data[height][width];
};
