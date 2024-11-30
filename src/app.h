#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game.h"

enum class GameState : uint8_t
{
    Init,
    GameOver,
    Playing
};

struct ApplicationLayout
{
    int height = 600;
    int width = 540;
    float pad_x = 30;
    float pad_y = 20;

    SDL_FRect score_rect{};
    SDL_FRect grid_rect{};

    ApplicationLayout()
    {
        const auto grid_size = static_cast<float>(width) - ((pad_x + 10) * 2.0f) + 15;

        score_rect = SDL_FRect(pad_x, pad_y, grid_size, 80);
        grid_rect = SDL_FRect(pad_x, static_cast<float>(height) - grid_size - pad_y - 10, grid_size, grid_size);
    }
};

class Application
{
  private:
    Game game;
    TTF_Font *font;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    GameState state = GameState::Init;
    ApplicationLayout layout;
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
