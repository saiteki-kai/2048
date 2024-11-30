#include "game_renderer.h"

#include "layout.h"

#include <cmath>

GameRenderer::GameRenderer(SDL_Renderer *renderer, TTF_Font *font) : renderer(renderer), font(font)
{
}

void GameRenderer::DrawText(const TextBox &text_box, const SDL_FRect &rect, const SDL_Color &background) const
{
    auto [x, y, w, h] = rect;
    x = rect.x + text_box.padding;
    y = rect.y + text_box.padding;
    w = rect.w - 2 * text_box.padding;
    h = rect.h - 2 * text_box.padding;

    TTF_SetFontSize(font, text_box.size); // adapt the font size to use the padded area

    SDL_Surface *surface = TTF_RenderText_LCD(font, text_box.text.c_str(), 0, text_box.color, background);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    const auto text_width = static_cast<float>(surface->w);
    const auto text_height = static_cast<float>(surface->h);

    SDL_FRect text_rect = {x, y, w, h};
    AlignTextRect(text_rect, text_height, text_width, text_box.alignment);

    SDL_RenderTexture(renderer, texture, nullptr, &text_rect);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

void GameRenderer::DrawScoreBox(const ScoreBox &box, const SDL_FRect &rect) const
{
    FillRect(renderer, &rect, box.bg_color);
    DrawText(box.label_text, rect, box.bg_color);
    DrawText(box.score_text, rect, box.bg_color);
}

void GameRenderer::DrawTile(const Tile &tile, const SDL_FRect &rect) const
{
    const auto idx = static_cast<size_t>(tile.value == 0 ? 0 : std::log2(tile.value));
    const auto &[background, foreground] = tile_colors.at(idx);

    // tile background
    FillRect(renderer, &rect, background);

    // tile text
    if (tile.value != 0)
    {
        const auto textbox = TextBox(std::to_string(tile.value), 50, 5, foreground, TextAlignment::Center);
        DrawText(textbox, rect, background);
    }
}

void GameRenderer::DrawGrid(const Grid &grid, const GridLayout &layout) const
{
    // grid background
    FillRect(renderer, &layout.rect, layout.fg_color);

    for (int row = 0; row < grid.Rows(); ++row)
    {
        for (int col = 0; col < grid.Cols(); ++col)
        {
            const Tile &tile = grid.GetTile(row, col);
            DrawTile(tile, layout.TileRect(row, col));
        }
    }
}

void GameRenderer::DrawScoreBoard(const uint32_t score, const uint32_t best, const ScoreBoardLayout &layout) const
{
    auto score_label = TextBox("Score", 16, 10, layout.score_fg_color, TextAlignment::Left);
    auto score_value = TextBox(std::to_string(score), 21, 10, layout.score_fg_color, TextAlignment::Right);

    auto best_label = TextBox("Best", 16, 10, layout.best_fg_color, TextAlignment::Left);
    auto best_value = TextBox(std::to_string(best), 21, 10, layout.best_fg_color, TextAlignment::Right);

    const auto score_box = ScoreBox(score_label, score_value, layout.score_bg_color);
    const auto best_box = ScoreBox(best_label, best_value, layout.best_bg_color);

    DrawScoreBox(score_box, layout.ScoreRect());
    DrawScoreBox(best_box, layout.BestRect());
}

void GameRenderer::DrawBackground(const SDL_Color &color) const
{
    FillRect(renderer, nullptr, color);
}
