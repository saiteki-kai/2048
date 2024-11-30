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

struct ScoreBox
{
    SDL_Color bg_color;
    SDL_Color text_color;
    uint32_t value;
    std::string label;

    ScoreBox(SDL_Color bg_color, SDL_Color text_color, uint32_t value, std::string label);
};

struct TextBox
{
    SDL_Color bg_color;
    SDL_Color text_color;
    TextAlignment alignment;
    std::string text;
    float size;
    float padding;

    TextBox(SDL_Color bg_color, SDL_Color text_color, TextAlignment alignment, std::string label, float size,
            float padding);
};

class GameRenderer
{
  private:
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;

  private:
    void SetRenderColor(const SDL_Color &color) const;
    void DrawTile(const Tile &tile, const SDL_FRect &rect) const;
    void DrawText(const TextBox &text_box, const SDL_FRect &rect) const;
    void DrawScoreBox(const ScoreBox &box, const SDL_FRect &rect) const;

  public:
    GameRenderer(SDL_Renderer *renderer, TTF_Font *font);
    void DrawBackground(const SDL_Color &color) const;
    void DrawGrid(const Grid &grid, const SDL_FRect &grid_rect) const;
    void DrawScoreBoard(const SDL_FRect &scores_rect, uint32_t score, uint32_t best) const;
};
