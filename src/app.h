#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game.h"
#include "style.h"

class Application
{
  private:
    Game game;
    TTF_Font *font;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running = false;

  public:
    Application();
    ~Application();

    void Run();
    void OnStart();
    void OnRender();
    void CheckWin();
    void OnEvent(const SDL_Event &event);
    void DrawGrid(const Grid &grid) const;
    void DrawTile(const Tile &tile, const SDL_FRect &rect) const;
    void DrawText(const char *text, const SDL_FRect &rect, const TileStyle &style, float size) const;
};

constexpr auto GetGridBackgroundRect() -> SDL_FRect;

void SetRenderColor(SDL_Renderer *renderer, const SDL_Color &color);
