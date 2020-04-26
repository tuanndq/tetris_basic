#pragma once
#include <SDL.h>

const int SQ = 30;

class Tetromino {
public:
    enum Type {I=0, J, L, T, O, Z, S};
    Tetromino(Type type);
    void draw(SDL_Renderer *);
    void draw_next(SDL_Renderer *);
    void move(int dx, int dy);
    void rotate();
    bool isBlock(int x, int y) const;
    int x() const;
    int y() const;
private:
    int _type;
    int _x;
    int _y;
    int _angle;
};
