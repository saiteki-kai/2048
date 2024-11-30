#include "app.h"

#include "game_renderer.h"
#include "style.h"

#include <cmath>
#include <iostream>

Application::Application()
{
    SDL_Init(SDL_INIT_VIDEO);

    if (!SDL_CreateWindowAndRenderer("2048", layout.width, layout.height, 0, &window, &renderer))
    {
        throw std::runtime_error(SDL_GetError());
    }

    if (!TTF_Init())
    {
        throw std::runtime_error(SDL_GetError());
    }

    const auto font_path = std::string(USER_FONT_PATH);
    font = TTF_OpenFont(font_path.c_str(), WindowStyle::FONT_SIZE);

    if (!font)
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Application::~Application()
{
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::Run()
{
    OnStart();

    SDL_Event event;

    while (running)
    {
        PoolEvents(event);
        OnRender();
        SDL_Delay(16);
    }
}

void Application::OnUpdate()
{
    game.Spawn();

    if (game.Lose())
    {
        std::cout << "Game Over\n";
        game.Reset();
    }

    if (game.Win())
    {
        std::cout << "Win\n";
    }
}

void Application::OnStart()
{
    running = true;
    game.Start();
}

void Application::PoolEvents(SDL_Event &event)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            running = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.key)
            {
            case SDLK_DOWN:
            case SDLK_S:
                game.Move(Direction::DOWN);
                OnUpdate();
                break;
            case SDLK_UP:
            case SDLK_W:
                game.Move(Direction::UP);
                OnUpdate();
                break;
            case SDLK_LEFT:
            case SDLK_A:
                game.Move(Direction::LEFT);
                OnUpdate();
                break;
            case SDLK_RIGHT:
            case SDLK_D:
                game.Move(Direction::RIGHT);
                OnUpdate();
                break;
            case SDLK_R:
                game.Reset();
            default:
                // Nothing to handle
                break;
            }
        }
    }
}

void Application::OnRender()
{
    SDL_RenderClear(renderer);

    const auto game_renderer = GameRenderer(renderer, font);                        // Refactor: init in the constructor
    game_renderer.DrawBackground(GridStyle::BG_COLOR);
    game_renderer.DrawScoreBoard(layout.score_rect, game.Score(), game.BestScore());
    game_renderer.DrawGrid(game.GetGrid(), layout.grid_rect);

    // display
    SDL_RenderPresent(renderer);
}
