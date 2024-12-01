#include "game_renderer.h"
#include "layout.h"

#include <cmath>

GameRenderer::GameRenderer(SDL_Renderer *renderer, TTF_Font *font) : renderer(renderer), font(font)
{
}

void GameRenderer::DrawText(const TextBox &text_box, const SDL_FRect &rect) const
{
    auto [x, y, w, h] = rect;
    x = rect.x + text_box.padding;
    y = rect.y + text_box.padding;
    w = rect.w - 2 * text_box.padding;
    h = rect.h - 2 * text_box.padding;

    TTF_SetFontSize(font, text_box.size);
    SDL_Surface *surface = TTF_RenderText_Blended(font, text_box.text.c_str(), 0, text_box.color);

    if (text_box.fit_container)
    {
        const auto font_size = AdjustFontSizeToFitRect(surface, font, text_box.text, text_box.size, h, w);

        TTF_SetFontSize(font, font_size);
        surface = TTF_RenderText_Blended(font, text_box.text.c_str(), 0, text_box.color);
    }

    const auto text_width = static_cast<float>(surface->w);
    const auto text_height = static_cast<float>(surface->h);

    SDL_FRect text_rect = {x, y, w, h};
    AlignTextRect(text_rect, text_height, text_width, text_box.alignment);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderTexture(renderer, texture, nullptr, &text_rect);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

void GameRenderer::DrawScoreBox(const ScoreBox &box, const SDL_FRect &rect) const
{
    FillRect(renderer, &rect, box.bg_color);
    DrawText(box.label_text, rect);
    DrawText(box.score_text, rect);
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
        const auto textbox = TextBox(std::to_string(tile.value), 50, 20, foreground, TextAlignment::Center, true);
        DrawText(textbox, rect);
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
    auto score_label = TextBox("Score", 16, 10, layout.score_fg_color, TextAlignment::Left, false);
    auto score_value = TextBox(std::to_string(score), 21, 10, layout.score_fg_color, TextAlignment::Right, false);

    auto best_label = TextBox("Best", 16, 10, layout.best_fg_color, TextAlignment::Left, false);
    auto best_value = TextBox(std::to_string(best), 21, 10, layout.best_fg_color, TextAlignment::Right, false);

    const auto score_box = ScoreBox(score_label, score_value, layout.score_bg_color);
    const auto best_box = ScoreBox(best_label, best_value, layout.best_bg_color);

    DrawScoreBox(score_box, layout.ScoreRect());
    DrawScoreBox(best_box, layout.BestRect());
}

void GameRenderer::DrawBackground(const SDL_Color &color) const
{
    FillRect(renderer, nullptr, color);
}

void GameRenderer::DrawInitScreen(const MessageLayout &layout) const
{
    FillRect(renderer, &layout.rect, layout.bg_color);

    constexpr std::string_view title = "Press any key to start";
    constexpr std::string_view subtitle = "Use WASD or arrow keys to move tiles";

    const auto title_box = TextBox(title, layout.title_size, 0, layout.fg_color, TextAlignment::Center, true);
    DrawText(title_box, layout.TitleRect());

    const auto subtitle_box = TextBox(subtitle, layout.subtitle_size, 10, layout.fg_color, TextAlignment::Center, true);
    DrawText(subtitle_box, layout.SubtitleRect());
}

void GameRenderer::DrawEndGameMessage(const MessageLayout &layout, const GameState &state) const
{
    FillRect(renderer, &layout.rect, layout.bg_color);

    std::string_view title;
    std::string_view subtitle;

    if (state == GameState::GameOver)
    {
        title = "Game Over!";
        subtitle = "Press 'R' to play again";
    }
    else
    {
        title = "Congratulations!";
        subtitle = "Press 'R' to play again";
    }

    const auto title_box = TextBox(title, layout.title_size, 0, layout.fg_color, TextAlignment::Center, false);
    DrawText(title_box, layout.TitleRect());

    const auto subtitle_box = TextBox(subtitle, layout.subtitle_size, 0, layout.fg_color, TextAlignment::Center, false);
    DrawText(subtitle_box, layout.SubtitleRect());
}
