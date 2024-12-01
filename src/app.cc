#include "app.h"
#include "game_renderer.h"

#include <cmath>
#include <iostream>

Application::Application()
{
    SDL_Init(SDL_INIT_VIDEO);

    if (!SDL_CreateWindowAndRenderer("2048", app_layout.width, app_layout.height, 0, &window, &renderer))
    {
        throw std::runtime_error(SDL_GetError());
    }

    if (!TTF_Init())
    {
        throw std::runtime_error(SDL_GetError());
    }

    const auto font_path = std::string(USER_FONT_PATH);
    font = TTF_OpenFont(font_path.c_str(), 50);

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
        state = GameState::GameOver;
    }

    if (game.Win())
    {
        std::cout << "Win\n";
    }
}

void Application::OnStart()
{
    running = true;
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
            if (event.key.key == SDLK_R)
            {
                game.Reset();
                state = GameState::Playing;
            }

            if (state == GameState::GameOver)
            {
                break;
            }

            if (state == GameState::Init)
            {
                state = GameState::Playing;
                game.Start();
                continue;
            }

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

    const auto game_renderer = GameRenderer(renderer, font); // TODO: (Refactor) init in the constructor

    game_renderer.DrawBackground(app_layout.grid_layout.bg_color);
    game_renderer.DrawScoreBoard(game.Score(), game.BestScore(), app_layout.score_board_layout);
    game_renderer.DrawGrid(game.GetGrid(), app_layout.grid_layout);

    if (state == GameState::Init)
    {
        game_renderer.DrawInitScreen(app_layout.message_layout);
    }
    else if (state == GameState::GameOver)
    {
        game_renderer.DrawGameOver(app_layout.message_layout);
    }

    // display
    SDL_RenderPresent(renderer);
}
