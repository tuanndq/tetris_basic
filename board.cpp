#include "board.hpp"

mainBoard::mainBoard() {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            data[i][j] = false;
        }
    }
}

void mainBoard::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 69, 0xff, 0xff, 0xff);

    //  draw line
    SDL_RenderDrawLine(renderer, 1, 1, 1, showHeight * SQ);
    SDL_RenderDrawLine(renderer, width * SQ - 1, 1, width * SQ - 1, showHeight * SQ);
    SDL_RenderDrawLine(renderer, 1, 1, width * SQ - 1, 1);
    SDL_RenderDrawLine(renderer, 1, showHeight * SQ - 1, width * SQ - 1, showHeight * SQ - 1);

    for (int y = 4; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //  draw brick
            if (data[y][x]) {
                SDL_Rect rect{x * SQ + 1, (y-4) * SQ + 1, SQ -2, SQ -2};
                SDL_RenderFillRect(renderer, &rect);
            }
            else {
                //  draw point
                SDL_RenderDrawPoint(renderer, x * SQ + SQ, (y-4) * SQ + SQ);
            }
        }
    }
}

bool mainBoard::collision(const Tetromino &t) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (t.isBlock(x, y)) {
                int xBrick = t.x() + x;
                int yBrick = t.y() + y;
                if (xBrick < 0 || xBrick >= width || yBrick >= height) {
                    return true;
                }
                if (data[yBrick][xBrick]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mainBoard::unite(const Tetromino &t) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (t.isBlock(x, y)) {
                data[t.y() + y][t.x() + x] = true;
            }
        }
    }

    for (int y = height - 1; y > 0; y--) {
        bool isFull = true;
        for (int x = 0; x < width; x++) {
            if (!data[y][x]) {
                isFull = false;
            }
        }
        if (isFull) {
            for (int newY = y; newY > 0; newY--) {
                for (int x = 0; x < width; x++) {
                    data[newY][x] = data[newY - 1][x];
                }
                for (int x = 0; x < width; x++) {
                    data[0][x] = false;
                }
            }
            score += 10;
            y++;
        }
    }
}

int mainBoard::getScore() const {
    return score;
}




