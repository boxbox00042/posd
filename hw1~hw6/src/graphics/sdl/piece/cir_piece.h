#pragma once

#include "piece.h"

class CirPiece : public Piece
{
private:
    int32_t _centreX;
    int32_t _centreY;
    int32_t _radius;

public:
    CirPiece(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius) : Piece(renderer), _centreX(centreX), _centreY(centreY), _radius(radius) {}

    void draw() override
    {
        // https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
        const int32_t diameter = (_radius * 2);
        int32_t x = (_radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        SDL_SetRenderDrawColor(_renderer, 0x46, 0x8D, 0xFF, 0xFF);
        while (x >= y)
        {
            SDL_RenderDrawPoint(_renderer, _centreX + x, _centreY - y);
            SDL_RenderDrawPoint(_renderer, _centreX + x, _centreY + y);
            SDL_RenderDrawPoint(_renderer, _centreX - x, _centreY - y);
            SDL_RenderDrawPoint(_renderer, _centreX - x, _centreY + y);
            SDL_RenderDrawPoint(_renderer, _centreX + y, _centreY - x);
            SDL_RenderDrawPoint(_renderer, _centreX + y, _centreY + x);
            SDL_RenderDrawPoint(_renderer, _centreX - y, _centreY - x);
            SDL_RenderDrawPoint(_renderer, _centreX - y, _centreY + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
};