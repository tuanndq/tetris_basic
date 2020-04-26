
#pragma once
#include <SDL.h>
#include "board.hpp"
#include <SDL_ttf.h>
#include <algorithm>

class Game {
public:
    Game();
    ~Game();
    bool tick();
private:
    Game(const Game &);
    Game &operator=(const Game &);
    SDL_Window *window;
    SDL_Renderer *renderer;
    //  draw text
    TTF_Font * font;
    SDL_Color color, color2;
    SDL_Surface * surface, * surface2;
    SDL_Texture * texture, * texture2;
    SDL_Rect dstrect, dstrect2;

    mainBoard _mainBoard;
    Tetromino _tetromino_before = Tetromino(static_cast<Tetromino::Type>(rand() % 7)),
              _tetromino;
    uint32_t _moveTime;
    uint32_t _moveLevel;
    int level;
    bool check(const Tetromino &);
};
