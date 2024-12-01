#pragma once

#include "game.h"
#include "layout.h"
#include "utils.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct TextBox
{
    std::string text;
    float size;
    float padding;
    SDL_Color color;
    TextAlignment alignment;
    bool fit_container = false;

    TextBox(const std::string_view text, const float size, const float padding, const SDL_Color color,
            const TextAlignment alignment, const bool fit_container)
        : text(text), size(size), padding(padding), color(color), alignment(alignment), fit_container(fit_container) {};
};

struct ScoreBox
{
    TextBox label_text;
    TextBox score_text;
    SDL_Color bg_color;

    ScoreBox(TextBox label_text, TextBox score_text, const SDL_Color &color)
        : label_text(std::move(label_text)), score_text(std::move(score_text)), bg_color(color) {};
};

class GameRenderer
{
  private:
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;

  private:
    void DrawTile(const Tile &tile, const SDL_FRect &rect) const;
    void DrawText(const TextBox &text_box, const SDL_FRect &rect) const;
    void DrawScoreBox(const ScoreBox &box, const SDL_FRect &rect) const;

  public:
    GameRenderer(SDL_Renderer *renderer, TTF_Font *font);
    void DrawBackground(const SDL_Color &color) const;
    void DrawGrid(const Grid &grid, const GridLayout &layout) const;
    void DrawScoreBoard(uint32_t score, uint32_t best, const ScoreBoardLayout &layout) const;
    void DrawInitScreen(const MessageLayout &layout) const;
    void DrawGameOver(const MessageLayout &layout) const;
};
