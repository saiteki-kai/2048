#include "app.h"

#include <cmath>
#include <iostream>

void SetRenderColor(SDL_Renderer *renderer, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

constexpr auto GetGridBackgroundRect() -> SDL_FRect
{
    constexpr float tile_space_x = static_cast<float>(GridStyle::TILE_SIZE + GridStyle::TILE_GAP) * GridStyle::N_COLS;
    constexpr float tile_space_y = static_cast<float>(GridStyle::TILE_SIZE + GridStyle::TILE_GAP) * GridStyle::N_ROWS;

    SDL_FRect rect;
    rect.x = (WindowStyle::WIDTH - tile_space_x) / 2;
    rect.y = (WindowStyle::HEIGHT - tile_space_y) / 2;
    rect.w = tile_space_x + GridStyle::TILE_GAP;
    rect.h = tile_space_y + GridStyle::TILE_GAP;

    return rect;
}

constexpr auto GetGridTileRect(const size_t row, const size_t col) -> SDL_FRect
{
    SDL_FRect rect;
    rect.x = static_cast<float>(col) * (GridStyle::TILE_SIZE + GridStyle::TILE_GAP) + GridStyle::TILE_OFFSET -
             GridStyle::TILE_GAP;
    rect.y = static_cast<float>(row) * (GridStyle::TILE_SIZE + GridStyle::TILE_GAP) + GridStyle::TILE_OFFSET -
             GridStyle::TILE_GAP;
    rect.w = GridStyle::TILE_SIZE;
    rect.h = GridStyle::TILE_SIZE;

    return rect;
}

Application::Application() : window(nullptr), renderer(nullptr)
{
    SDL_Init(SDL_INIT_VIDEO);

    if (!SDL_CreateWindowAndRenderer("2048", WindowStyle::WIDTH, WindowStyle::HEIGHT, 0, &window, &renderer))
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
        while (SDL_PollEvent(&event))
        {
            OnEvent(event);
        }

        OnRender();
    }
}

void Application::CheckWin()
{
    game.Spawn();

    // if (!game.CanMove())
    // {
    //     std::cout << "Game Over\n";
    //     // TODO: display game over screen
    //     // TODO: reset game
    //     SDL_Delay(3000);
    //     game.Reset();
    // }

    if (game.CheckWin())
    {
        // WIN
    }
}

void Application::OnStart()
{
    running = true;
    game.Start();
}

void Application::OnEvent(const SDL_Event &event)
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
            CheckWin();
            break;
        case SDLK_UP:
        case SDLK_W:
            game.Move(Direction::UP);
            CheckWin();
            break;
        case SDLK_LEFT:
        case SDLK_A:
            game.Move(Direction::LEFT);
            CheckWin();
            break;
        case SDLK_RIGHT:
        case SDLK_D:
            game.Move(Direction::RIGHT);
            CheckWin();
            break;
        default:
            // Nothing to handle
            break;
        }
    }
}

void Application::OnRender()
{
    SDL_RenderClear(renderer);

    // background
    SetRenderColor(renderer, GridStyle::BG_COLOR);
    SDL_RenderFillRect(renderer, nullptr);

    // score
    constexpr SDL_FRect score_rect = {WindowStyle::WIDTH / 2.0f, 20, 48, 16};
    DrawText(std::to_string(game.Score()).c_str(), score_rect, TileStyle(GridStyle::BG_COLOR, SDL_Color{0, 0, 0, 0}));

    // grid
    constexpr SDL_FRect rect = GetGridBackgroundRect();
    SetRenderColor(renderer, GridStyle::FG_COLOR);
    SDL_RenderFillRect(renderer, &rect);

    // draw grid
    DrawGrid(game.GetGrid());

    SDL_RenderPresent(renderer);
}

void Application::DrawGrid(const Grid &grid) const
{
    for (int row = 0; row < grid.Rows(); ++row)
    {
        for (int col = 0; col < grid.Cols(); ++col)
        {
            SDL_FRect rect = GetGridTileRect(row, col);
            const Tile &tile = grid.GetTile(row, col);
            DrawTile(tile, rect);
        }
    }
}

void Application::DrawTile(const Tile &tile, const SDL_FRect &rect) const
{
    const auto idx = static_cast<size_t>(tile.value == 0 ? 0 : log2(tile.value));
    const TileStyle &style = tile_colors.at(idx);

    // background
    SetRenderColor(renderer, style.background);
    SDL_RenderFillRect(renderer, &rect);

    // text
    if (tile.value != 0)
    {
        const std::string str = std::to_string(tile.value);
        DrawText(str.c_str(), rect, style);
    }
}

void Application::DrawText(const char *text, const SDL_FRect &rect, const TileStyle &style) const
{
    SDL_Surface *surface = TTF_RenderText_LCD(font, text, 0, style.foreground, style.background);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    const auto text_width = static_cast<float>(surface->w);
    const auto text_height = static_cast<float>(surface->h);

    SDL_FRect textRect;
    textRect.x = rect.x + (rect.w - text_width) / 2;
    textRect.y = rect.y + (rect.h - text_height) / 2;
    textRect.w = text_width;
    textRect.h = text_height;

    SDL_RenderTexture(renderer, texture, nullptr, &textRect);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}
