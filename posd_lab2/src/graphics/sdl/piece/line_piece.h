#pragma once

#include "piece.h"

class LinePiece : public Piece
{
private:
    SDL_Point *_points;
    int _size;

public:
    LinePiece(SDL_Renderer *renderer, SDL_Point *points, int size) : Piece(renderer), _points(points), _size(size) {}
    ~LinePiece()
    {
        delete[] _points;
    }
    void draw() override
    {
        if (_size > 4)
        {
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xBE, 0x0B, 0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x6E, 0xFF);
        }
        SDL_RenderDrawLines(_renderer, _points, _size);
    }
};