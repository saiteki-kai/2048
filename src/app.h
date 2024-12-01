#pragma once

#include "game.h"
#include "game_renderer.h"
#include "layout.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

enum class GameState : uint8_t
{
    Startup,
    GameOver,
    Playing,
    Victory,
};

struct Application
{
  private:
    Game game;
    TTF_Font *font = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    ApplicationLayout app_layout;
    std::unique_ptr<GameRenderer> game_renderer;
    GameState state = GameState::Startup;
    bool running = false;

  private:
    void Init();
    void Quit() const;
    void PoolEvents(SDL_Event &event);
    auto HandleKeyDownEvent(const SDL_Event &event) -> bool;
    void CheckGameState();
    void Render();

  public:
    void Run();
};
