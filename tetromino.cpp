#include "tetromino.hpp"

Tetromino::Tetromino(Type type) {
    _type = type;
    _x = 3;
    _y = 0;
    _angle  = 0;
}

void Tetromino::draw(SDL_Renderer *renderer) {
    switch (_type) {
        case I:
        SDL_SetRenderDrawColor(renderer, 15, 020, 254, 123);
        break;
      case J:
        SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
        break;
      case L:
        SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
        break;
      case O:
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x7f, 0xff);
        break;
      case S:
        SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff);
        break;
      case T:
        SDL_SetRenderDrawColor(renderer, 0x7f, 0x40, 0x00, 0xff);
        break;
      case Z:
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x7f, 0xff);
        break;
    }

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (isBlock(x, y)) {
                SDL_Rect rect{(x + _x) * SQ + 1, (y + _y - 4) * SQ + 1, SQ - 2, SQ - 2};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Tetromino::draw_next(SDL_Renderer *renderer) {
    switch (_type) {
        case I:
        SDL_SetRenderDrawColor(renderer, 15, 020, 254, 123);
        break;
      case J:
        SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
        break;
      case L:
        SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
        break;
      case O:
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x7f, 0xff);
        break;
      case S:
        SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff);
        break;
      case T:
        SDL_SetRenderDrawColor(renderer, 0x7f, 0x40, 0x00, 0xff);
        break;
      case Z:
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x7f, 0xff);
        break;
    }

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (isBlock(x, y)) {
                SDL_Rect rect{(x + _x * 4.4) * SQ + 1, (y + _y + 3) * SQ + 1, SQ - 2, SQ - 2};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Tetromino::move(int dx, int dy) {
    _x += dx;
    _y += dy;
}

void Tetromino::rotate() {
    _angle += 1;
    _angle %= 4;
}

bool Tetromino::isBlock(int x, int y) const {
    static const char *shape[][4] = {
        {
          " *  "
          " *  "
          " *  "
          " *  ",
          "    "
          "****"
          "    "
          "    ",
          " *  "
          " *  "
          " *  "
          " *  ",
          "    "
          "****"
          "    "
          "    ",
        },
        {
          "  * "
          "  * "
          " ** "
          "    ",
          "    "
          "*   "
          "*** "
          "    ",
          " ** "
          " *  "
          " *  "
          "    ",
          "    "
          "    "
          "*** "
          "  * ",
        },
        {
          " *  "
          " *  "
          " ** "
          "    ",
          "    "
          "*** "
          "*   "
          "    ",
          " ** "
          "  * "
          "  * "
          "    ",
          "  * "
          "*** "
          "    "
          "    ",
        },
        {
          "    "
          " ** "
          " ** "
          "    ",
          "    "
          " ** "
          " ** "
          "    ",
          "    "
          " ** "
          " ** "
          "    ",
          "    "
          " ** "
          " ** "
          "    ",
        },
        {
          "  * "
          " ** "
          " *  "
          "    ",
          "    "
          "**  "
          " ** "
          "    ",
          "  * "
          " ** "
          " *  "
          "    ",
          "    "
          "**  "
          " ** "
          "    ",
        },
        {
          " *  "
          " ** "
          " *  "
          "    ",
          "    "
          "*** "
          " *  "
          "    ",
          " *  "
          "**  "
          " *  "
          "    ",
          " *  "
          "*** "
          "    "
          "    ",
        },
        {
          " *  "
          " ** "
          "  * "
          "    ",
          "    "
          " ** "
          "**  "
          "    ",
          " *  "
          " ** "
          "  * "
          "    ",
          "    "
          " ** "
          "**  "
          "    ",
        },
    };
    return shape[_type][_angle][x + y*4] == '*';
}

int Tetromino::x() const {
    return _x;
}

int Tetromino::y() const {
    return _y;
}
