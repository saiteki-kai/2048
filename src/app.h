#pragma once

#include "game.h"
#include "layout.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

enum class GameState : uint8_t
{
    Init,
    GameOver,
    Playing
};

class Application
{
  private:
    Game game;
    TTF_Font *font;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    GameState state = GameState::Init;
    ApplicationLayout app_layout;
    bool running = false;

  public:
    Application();
    ~Application();

    void Run();
    void OnStart();
    void OnRender();
    void OnUpdate();
    void PoolEvents(SDL_Event &event);
};
