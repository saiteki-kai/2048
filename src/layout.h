#pragma once

#include <SDL3/SDL.h>
#include <array>

struct MessageLayout
{
    SDL_Color fg_color = {255, 255, 255, 0xff};
    SDL_Color bg_color = {0, 0, 0, 150};

    SDL_FRect rect;

    float offset_y = 35;
    float title_size = 65;
    float subtitle_size = 45;
    float vertical_gap = 40;

    explicit MessageLayout(const SDL_FRect &rect) : rect(rect)
    {
    }

    [[nodiscard]] auto TitleRect() const -> SDL_FRect;
    [[nodiscard]] auto SubtitleRect() const -> SDL_FRect;
    [[nodiscard]] auto TotalSize() const -> float;
};

struct ScoreBoardLayout
{
    SDL_Color score_bg_color = {234, 231, 217, 0xff};
    SDL_Color score_fg_color = {152, 136, 118, 0xff};
    SDL_Color best_bg_color = {234, 231, 217, 0xff};
    SDL_Color best_fg_color = {152, 136, 118, 0xff};

    SDL_FRect rect;

    float middle_gap = 20.0f;
    float box_height = 50;
    float box_width = 0;

    explicit ScoreBoardLayout(const SDL_FRect &score_board_rect)
        : rect(score_board_rect), box_width((rect.w - middle_gap) / 2.0f)
    {
    }

    [[nodiscard]] auto ScoreRect() const -> SDL_FRect;
    [[nodiscard]] auto BestRect() const -> SDL_FRect;
};

struct TileStyle
{
    SDL_Color background;
    SDL_Color foreground;

    static constexpr SDL_Color DarkText = {0x77, 0x6e, 0x65, 0xff};
    static constexpr SDL_Color LightText = {0xff, 0xff, 0xff, 0xff};
};

struct GridLayout
{
    SDL_Color bg_color = {0xfa, 0xf8, 0xef, 0xff};
    SDL_Color fg_color = {0xbb, 0xad, 0xa0, 0xff};

    SDL_FRect rect;

    float tile_gap = 15;
    float tile_size = 100;
    float tile_offset = 100;

    explicit GridLayout(const SDL_FRect &grid_rect) : rect(grid_rect)
    {
    }

    [[nodiscard]] auto TileRect(size_t row, size_t col) const -> SDL_FRect;
};

static constexpr std::array tile_colors = {
    TileStyle(SDL_Color(0xee, 0xe4, 0xda, 0x59), TileStyle::DarkText),
    TileStyle(SDL_Color(0xee, 0xe4, 0xda, 0xff), TileStyle::DarkText),
    TileStyle(SDL_Color(0xed, 0xe0, 0xc8, 0xff), TileStyle::DarkText),
    TileStyle(SDL_Color(0xf2, 0xb1, 0x79, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xf5, 0x95, 0x63, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xf6, 0x7c, 0x5f, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xf6, 0x5e, 0x3b, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xed, 0xcf, 0x72, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xed, 0xc6, 0x61, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xed, 0xc8, 0x50, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xed, 0xc5, 0x3f, 0xff), TileStyle::LightText),
    TileStyle(SDL_Color(0xed, 0xc2, 0x2e, 0xff), TileStyle::LightText),
};

struct ApplicationLayout
{
    int height = 600;
    int width = 540;
    float pad_x = 30;
    float pad_y = 20;

    GridLayout grid_layout;
    ScoreBoardLayout score_board_layout;
    MessageLayout message_layout;

    ApplicationLayout() : grid_layout(GridRect()), score_board_layout(ScoreBoardRect()), message_layout(GridRect())
    {
    }

    [[nodiscard]] constexpr auto GridSize() const;
    [[nodiscard]] auto ScoreBoardRect() const -> SDL_FRect;
    [[nodiscard]] auto GridRect() const -> SDL_FRect;
};