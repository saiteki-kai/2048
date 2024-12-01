#include "app.h"
#include "game_renderer.h"

#include <cmath>
#include <iostream>

void Application::Init()
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

    game_renderer = std::make_unique<GameRenderer>(renderer, font);
}

void Application::Quit() const
{
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::Run()
{
    Init();

    running = true;

    SDL_Event event;

    while (running)
    {
        PoolEvents(event);
        Render();
        SDL_Delay(16);
    }

    Quit();
}

void Application::CheckGameState()
{
    if (game.Lose())
    {
        state = GameState::GameOver;
    }

    if (game.Win())
    {
        state = GameState::Victory;
    }
}

auto Application::HandleKeyDownEvent(const SDL_Event &event) -> bool
{
    if (event.key.key == SDLK_R)
    {
        game.Reset();
        state = GameState::Playing;
        return false;
    }

    switch (state)
    {
    case GameState::Startup:
        state = GameState::Playing;
        game.Start();
        return false;
    case GameState::GameOver:
        return true;
    case GameState::Playing:
    default:
        switch (event.key.key)
        {
        case SDLK_DOWN:
        case SDLK_S:
            game.Move(Direction::DOWN);
            break;
        case SDLK_UP:
        case SDLK_W:
            game.Move(Direction::UP);
            break;
        case SDLK_LEFT:
        case SDLK_A:
            game.Move(Direction::LEFT);
            break;
        case SDLK_RIGHT:
        case SDLK_D:
            game.Move(Direction::RIGHT);
            break;
        default:
            return false;
        }

        game.Spawn();
        CheckGameState();

        return false;
    }
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
            if (HandleKeyDownEvent(event))
            {
                break;
            }
        }
    }
}

void Application::Render()
{
    SDL_RenderClear(renderer);

    game_renderer->DrawBackground(app_layout.grid_layout.bg_color);
    game_renderer->DrawScoreBoard(game.Score(), game.BestScore(), app_layout.score_board_layout);
    game_renderer->DrawGrid(game.GetGrid(), app_layout.grid_layout);

    if (state == GameState::Startup)
    {
        game_renderer->DrawInitScreen(app_layout.message_layout);
    }
    else if (state == GameState::GameOver || state == GameState::Victory)
    {
        game_renderer->DrawEndGameMessage(app_layout.message_layout, state);
    }

    // display
    SDL_RenderPresent(renderer);
}
