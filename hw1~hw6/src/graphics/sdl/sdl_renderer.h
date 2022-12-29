#pragma once

#include "sdl.h"
#include "./piece/cir_piece.h"
#include "./piece/line_piece.h"
#include "../event_listener.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class SDLRenderer : public SDL
{
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    double _xOffset;
    double _yOffset;
    double _scale;
    SDL_Window *_window = NULL;
    SDL_Renderer *_renderer = NULL;
    std::vector<Piece *> _pieces;
    EventListener *_eventListener;

public:
    SDLRenderer(double scale, EventListener *eventListener) : _scale(scale), _eventListener(eventListener) {}

    ~SDLRenderer()
    {
        destroy();
    }

    void init(int width, int height) override
    {
        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;
        _xOffset = SCREEN_WIDTH / 2;
        _yOffset = SCREEN_HEIGHT / 2;

        bool success = true;
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            {
                printf("Warning: Linear texture filtering not enabled!");
            }
            SDL_DisplayMode DM;
            int displayWidth = SCREEN_WIDTH / 2;
            int displayHeight = SCREEN_HEIGHT / 2;
            if (SDL_GetCurrentDisplayMode(0, &DM) == 0)
            {
                displayWidth = DM.w;
                displayHeight = DM.h;
            }
            else
            {
                printf("Failed to get the display size. Use the default position (0, 0).");
            }
            _window = SDL_CreateWindow(
                "SDL Tutorial",
                (displayWidth / 2) - (SCREEN_WIDTH / 2),
                (displayHeight / 2) - (SCREEN_HEIGHT / 2),
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);
            if (_window == NULL)
            {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
                if (_renderer == NULL)
                {
                    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;
                }
                else
                {
                    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                        success = false;
                    }
                }
            }
        }
        if (!success)
        {
            printf("Failed to initialize!\n");
        }
    };

    void renderDrawLines(double *points, int size) override
    {
        SDL_Point *sdlPoints = new SDL_Point[size / 2 + 1];
        for (int i = 0; i < size; i += 2)
        {
            sdlPoints[i / 2] = SDL_Point{
                (int)(_xOffset + points[i] * _scale),
                (int)(_yOffset - points[i + 1] * _scale)};
        }
        sdlPoints[size / 2] = SDL_Point{
            (int)(_xOffset + points[0] * _scale),
            (int)(_yOffset - points[1] * _scale)};
        _pieces.push_back(
            new LinePiece(_renderer, sdlPoints, size / 2 + 1));
    };

    void renderDrawCircle(double centreX, double centreY, double radius) override
    {
        _pieces.push_back(
            new CirPiece(
                _renderer,
                (int)(_xOffset + centreX * _scale),
                (int)(_yOffset - centreY * _scale),
                (int)(radius * _scale)));
    };

    void handle(SDL_Event e)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        double rx = (x - _xOffset) / _scale;
        double ry = (_yOffset - y) / _scale;
        if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT)
        {
            _eventListener->leftMouseMove(rx, ry);
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            _eventListener->leftMouseDown(rx, ry);
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
        {
            _eventListener->rightMouseDown(rx, ry);
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
        {
            _eventListener->leftMouseUp(rx, ry);
        }
    }

    void refresh()
    {
        for (std::vector<Piece *>::iterator it = _pieces.begin(); it != _pieces.end(); it++)
            delete (*it);
        _pieces.clear();
        SDL_SetRenderDrawColor(_renderer, 0x00, 0x1D, 0x3D, 0xFF);
        SDL_RenderClear(_renderer);
        SDL_SetRenderDrawColor(_renderer, 0xED, 0xED, 0xE9, 0xFF);
        for (int i = 0; i < SCREEN_HEIGHT; i += 4)
            SDL_RenderDrawPoint(_renderer, SCREEN_WIDTH / 2, i);
        for (int i = 0; i < SCREEN_WIDTH; i += 4)
            SDL_RenderDrawPoint(_renderer, i, SCREEN_HEIGHT / 2);
        int x, y;
        SDL_GetMouseState(&x, &y);
        double rx = (x - _xOffset) / _scale;
        double ry = (_yOffset - y) / _scale;
        _eventListener->refresh(rx, ry);
    }

    void renderPresent() override
    {
        SDL_Event e;
        bool quit = false;

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;
                handle(e);
            }
            refresh();
            for (std::vector<Piece *>::iterator it = _pieces.begin(); it != _pieces.end(); it++)
                (*it)->draw();
            SDL_RenderPresent(_renderer);
            SDL_Delay(50);
        }
    }

    void destroy() override
    {
        for (std::vector<Piece *>::iterator it = _pieces.begin(); it != _pieces.end(); it++)
            delete (*it);
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        _renderer = NULL;
        _window = NULL;
        IMG_Quit();
        SDL_Quit();
    }
};