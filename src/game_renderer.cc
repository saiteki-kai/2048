#include "game_renderer.h"

#include "style.h"

#include <cmath>
#include <utility>

ScoreBox::ScoreBox(const SDL_Color bg_color, const SDL_Color text_color, const uint32_t value, std::string label)
    : bg_color(bg_color), text_color(text_color), value(value), label(std::move(label))
{
}

TextBox::TextBox(const SDL_Color bg_color, const SDL_Color text_color, const TextAlignment alignment, std::string label,
                 const float size, const float padding)
    : bg_color(bg_color), text_color(text_color), alignment(alignment), text(std::move(label)), size(size),
      padding(padding)
{
}

void GameRenderer::SetRenderColor(const SDL_Color &color) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void GameRenderer::DrawText(const TextBox &text_box, const SDL_FRect &rect) const
{
    auto [x, y, w, h] = rect;
    x = rect.x + text_box.padding;
    y = rect.y + text_box.padding;
    w = rect.w - 2 * text_box.padding;
    h = rect.h - 2 * text_box.padding;

    TTF_SetFontSize(font, text_box.size); // adapt the font size to use the padded area

    SDL_Surface *surface = TTF_RenderText_LCD(font, text_box.text.c_str(), 0, text_box.bg_color, text_box.text_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    const auto text_width = static_cast<float>(surface->w);
    const auto text_height = static_cast<float>(surface->h);

    SDL_FRect textRect;

    switch (text_box.alignment)
    {
    case TextAlignment::Left:
        textRect.x = x;
        break;
    case TextAlignment::Right:
        textRect.x = x + w - text_width;
        break;
    case TextAlignment::Center:
    default:
        textRect.x = x + (w - text_width) / 2;
        break;
    }

    textRect.y = y + (h - text_height) / 2;
    textRect.w = text_width;
    textRect.h = text_height;

    SDL_RenderTexture(renderer, texture, nullptr, &textRect);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

void GameRenderer::DrawScoreBox(const ScoreBox &box, const SDL_FRect &rect) const
{
    SetRenderColor(box.bg_color);
    SDL_RenderFillRect(renderer, &rect);

    const auto label = TextBox(box.text_color, box.bg_color, TextAlignment::Left, box.label, 16, 10);
    const auto value = TextBox(box.text_color, box.bg_color, TextAlignment::Right, std::to_string(box.value), 21, 10);

    DrawText(label, rect);
    DrawText(value, rect);
}

GameRenderer::GameRenderer(SDL_Renderer *renderer, TTF_Font *font) : renderer(renderer), font(font)
{
}

constexpr auto GetGridTileRect(const size_t row, const size_t col, const SDL_FRect &grid_rect) -> SDL_FRect
{
    SDL_FRect rect;
    rect.x = grid_rect.x + static_cast<float>(col) * GridStyle::TILE_SIZE + (col + 1) * GridStyle::TILE_GAP;
    rect.y = grid_rect.y + static_cast<float>(row) * GridStyle::TILE_SIZE + (row + 1) * GridStyle::TILE_GAP;
    rect.w = GridStyle::TILE_SIZE;
    rect.h = GridStyle::TILE_SIZE;

    return rect;
}

void GameRenderer::DrawTile(const Tile &tile, const SDL_FRect &rect) const
{
    const auto idx = static_cast<size_t>(tile.value == 0 ? 0 : std::log2(tile.value));
    const TileStyle &style = tile_colors.at(idx);

    // tile background
    SetRenderColor(style.background);
    SDL_RenderFillRect(renderer, &rect);

    // tile text
    if (tile.value != 0)
    {
        const std::string str = std::to_string(tile.value);
        const auto textbox = TextBox(style.foreground, style.background, TextAlignment::Center, str, 50, 5);
        DrawText(textbox, rect);
    }
}

void GameRenderer::DrawGrid(const Grid &grid, const SDL_FRect &grid_rect) const
{
    // grid background
    SetRenderColor(GridStyle::FG_COLOR);
    SDL_RenderFillRect(renderer, &grid_rect);

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

void GameRenderer::DrawScoreBoard(const SDL_FRect &scores_rect, const uint32_t score, const uint32_t best) const
{
    // Colors
    constexpr SDL_Color bg_color = {234, 231, 217, 0xff};
    constexpr SDL_Color text_color = {152, 136, 118, 0xff};

    // Layout Constants
    constexpr float middle_gap = 20.0f;
    const float box_width = (scores_rect.w - middle_gap) / 2;
    constexpr int box_height = 50;

    // Rectangles for the boxes
    const SDL_FRect score_rect = {scores_rect.x, scores_rect.y, box_width, box_height};
    const SDL_FRect best_rect = {scores_rect.x + box_width + middle_gap, scores_rect.y, box_width, box_height};

    const auto scoreBox = ScoreBox(bg_color, text_color, score, "Score");
    const auto bestBox = ScoreBox(bg_color, text_color, best, "Best");

    DrawScoreBox(scoreBox, score_rect);
    DrawScoreBox(bestBox, best_rect);
}

void GameRenderer::DrawBackground(const SDL_Color &color) const
{
    SetRenderColor(color);
    SDL_RenderFillRect(renderer, nullptr);
}
