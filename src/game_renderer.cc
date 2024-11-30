#include "game_renderer.h"
#include "style.h"

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

constexpr auto GetGridTileRect(const size_t row, const size_t col, const SDL_FRect &grid_rect) -> SDL_FRect
{
    const auto i = static_cast<float>(col);
    const auto j = static_cast<float>(row);

    SDL_FRect rect;
    rect.x = grid_rect.x + i * GridStyle::TILE_SIZE + (i + 1) * GridStyle::TILE_GAP;
    rect.y = grid_rect.y + j * GridStyle::TILE_SIZE + (j + 1) * GridStyle::TILE_GAP;
    rect.w = GridStyle::TILE_SIZE;
    rect.h = GridStyle::TILE_SIZE;

    return rect;
}

void GameRenderer::DrawTile(const Tile &tile, const SDL_FRect &rect) const
{
    const auto idx = static_cast<size_t>(tile.value == 0 ? 0 : std::log2(tile.value));
    const TileStyle &style = tile_colors.at(idx);

    // tile background
    FillRect(renderer, &rect, style.background);

    // tile text
    if (tile.value != 0)
    {
        const auto textbox = TextBox(std::to_string(tile.value), 50, 5, style.foreground, TextAlignment::Center);
        DrawText(textbox, rect, style.background);
    }
}

void GameRenderer::DrawGrid(const Grid &grid, const SDL_FRect &grid_rect) const
{
    // grid background
    FillRect(renderer, &grid_rect, GridStyle::FG_COLOR);

    for (int row = 0; row < grid.Rows(); ++row)
    {
        for (int col = 0; col < grid.Cols(); ++col)
        {
            SDL_FRect rect = GetGridTileRect(row, col, grid_rect);
            const Tile &tile = grid.GetTile(row, col);
            DrawTile(tile, rect);
        }
    }
}

void GameRenderer::DrawScoreBoard(const uint32_t score, const uint32_t best, const SDL_FRect &scores_rect) const
{
    constexpr SDL_Color bg_color = {234, 231, 217, 0xff};
    constexpr SDL_Color text_color = {152, 136, 118, 0xff};

    constexpr int box_height = 50;
    constexpr float middle_gap = 20.0f;
    const float box_width = (scores_rect.w - middle_gap) / 2.0f;

    const SDL_FRect score_rect = {scores_rect.x, scores_rect.y, box_width, box_height};
    const SDL_FRect best_rect = {scores_rect.x + box_width + middle_gap, scores_rect.y, box_width, box_height};

    auto score_label = TextBox("Score", 16, 10, text_color, TextAlignment::Left);
    auto score_value = TextBox(std::to_string(score), 21, 10, text_color, TextAlignment::Right);

    auto best_label = TextBox("Best", 16, 10, text_color, TextAlignment::Left);
    auto best_value = TextBox(std::to_string(best), 21, 10, text_color, TextAlignment::Right);

    const auto score_box = ScoreBox(score_label, score_value, bg_color);
    const auto best_box = ScoreBox(best_label, best_value, bg_color);

    DrawScoreBox(score_box, score_rect);
    DrawScoreBox(best_box, best_rect);
}

void GameRenderer::DrawBackground(const SDL_Color &color) const
{
    FillRect(renderer, nullptr, color);
}
