
#include "onGame.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include <SDL_image.h>

const int flowTime[7] = {1000, 850, 700, 550, 400, 250, 100};

Game::Game():
    _tetromino{static_cast<Tetromino::Type>(rand() % 7)}
{
    _moveTime  = SDL_GetTicks();
    level = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");
    window = SDL_CreateWindow("Tetris basic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2*width*SQ, showHeight*SQ, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //  draw text
    TTF_Init();
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 20);
    if (!font) {
        std::cout << TTF_GetError();
    }
    color = { 69, 255, 255 };
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

bool Game::tick()
{
    // draw level text

    std::string l = "Level: ";
    std::string s = "Scores: ";
    std::string str_level = std::to_string(level + 1);
    int scr = _mainBoard.getScore();
    std::string str_score = std::to_string(scr);
    l += str_level;
    s += str_score;

    surface = TTF_RenderText_Solid(font, l.c_str(), color);
    surface2 = TTF_RenderText_Solid(font, s.c_str(), color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_QueryTexture(texture2, NULL, NULL, &texW, &texH);

    dstrect = { width * SQ + 15, showHeight * SQ / 2 , texW, texH };
    dstrect2 = { width * SQ + 15, showHeight * SQ / 2 + 150, texW, texH };

  //    event listener
  SDL_Event e;
  if (SDL_WaitEventTimeout(&e, 200))
  {
    switch (e.type)
    {
    case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_DOWN:
          {
            Tetromino t = _tetromino;
            t.move(0, 1);
            if (!_mainBoard.collision(t))
              _tetromino = t;
          }
          break;
        case SDLK_RIGHT:
          {
            Tetromino t = _tetromino;
            t.move(1, 0);
            if (!_mainBoard.collision(t))
              _tetromino = t;
          }
          break;
        case SDLK_LEFT:
          {
            Tetromino t = _tetromino;
            t.move(-1, 0);
            if (!_mainBoard.collision(t))
              _tetromino = t;
          }
          break;
        case SDLK_UP:
          {
            Tetromino t = _tetromino;
            t.rotate();
            if (!_mainBoard.collision(t))
              _tetromino = t;
          }
          break;
        case SDLK_ESCAPE:
            return false;
        }
      }
      break;
    case SDL_QUIT:
        return false;
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  _mainBoard.draw(renderer);
  _tetromino.draw(renderer);
  _tetromino_before.draw_next(renderer);
  //    text
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  SDL_RenderCopy(renderer, texture2, NULL, &dstrect2);

  if (level < 6) {
    if (_mainBoard.getScore() > flowTime[6 - level]) {
        level++;
    }
  }
  if (SDL_GetTicks() > _moveTime)
  {
    _moveTime += flowTime[level];
    Tetromino t = _tetromino;
    t.move(0, 1);
    if (!check(t)) return false;
  }
  SDL_RenderPresent(renderer);
  return true;
};

bool Game::check(const Tetromino &t) {
    if (_mainBoard.collision(t)) {
        _mainBoard.unite(_tetromino);
        _tetromino = _tetromino_before;
        _tetromino_before = {static_cast<Tetromino::Type>(rand() % 7)};
        if (_mainBoard.collision(_tetromino)) {

            //  load image game over
            IMG_Init(IMG_INIT_PNG);
            texture = IMG_LoadTexture(renderer, "gameOver.png");
            color2 = {255, 255, 255};
            surface = TTF_RenderText_Solid(font, "Press R to replay!", color2);
            texture2 = SDL_CreateTextureFromSurface(renderer, surface);
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(texture2, NULL, NULL, &texW, &texH);
            dstrect2 = {(width+2) * SQ, (13) * SQ, texW, texH};

            SDL_Event e;
            bool onGame = true;
            while (onGame) {
                SDL_Rect dstrect = { (2*width*SQ-520)/2, (showHeight*SQ-113)/2, 520, 113 };
                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_RenderCopy(renderer, texture2, NULL, &dstrect2);
                SDL_RenderPresent(renderer);
                SDL_WaitEvent(&e);
                switch (e.type) {
                    case SDL_QUIT:
                        return false;
                    case SDL_KEYDOWN:
                        if (e.key.keysym.sym == SDLK_r) {
                            onGame = false;
                            break;
                        }
                }
            }
            SDL_DestroyTexture(texture);
            level = 0;
            _mainBoard = mainBoard();
        }
    }
    else {
        _tetromino = t;
    }
    return true;
}


