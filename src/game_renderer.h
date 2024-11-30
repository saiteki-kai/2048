#pragma once

#include "game.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

enum class TextAlignment : uint8_t
{
    Left,
    Center,
    Right,
};

struct TextBox
{
    std::string text;
    float size;
    float padding;
    SDL_Color color;
    TextAlignment alignment;

    TextBox(std::string_view text, float size, float padding, SDL_Color color, TextAlignment alignment);
};

struct ScoreBox
{
    TextBox label_text;
    TextBox score_text;
    SDL_Color bg_color;

    ScoreBox(TextBox &label_text, TextBox &score_text, const SDL_Color &color);
};

class GameRenderer
{
  private:
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;

  private:
    void SetRenderColor(const SDL_Color &color) const;
    void DrawTile(const Tile &tile, const SDL_FRect &rect) const;
    void DrawText(const TextBox &text_box, const SDL_FRect &rect, const SDL_Color &background) const;
    void DrawScoreBox(const ScoreBox &box, const SDL_FRect &rect) const;

  public:
    GameRenderer(SDL_Renderer *renderer, TTF_Font *font);
    void DrawBackground(const SDL_Color &color) const;
    void DrawGrid(const Grid &grid, const SDL_FRect &grid_rect) const;
    void DrawScoreBoard(uint32_t score, uint32_t best, const SDL_FRect &scores_rect) const;
};
