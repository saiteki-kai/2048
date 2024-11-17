#pragma once

#include <SDL3/SDL.h>

#include <array>

struct TileStyle
{
  SDL_Color background;
  SDL_Color foreground;

  static constexpr SDL_Color DarkText = {0x77, 0x6e, 0x65, 0xff};
  static constexpr SDL_Color LightText = {0xff, 0xff, 0xff, 0xff};
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

struct GridStyle
{
  static constexpr SDL_Color BG_COLOR = {0xfa, 0xf8, 0xef, 0xff};
  static constexpr SDL_Color FG_COLOR = {0xbb, 0xad, 0xa0, 0xff};

  static constexpr int N_ROWS = 4;
  static constexpr int N_COLS = 4;

  static constexpr int TILE_GAP = 15;
  static constexpr int TILE_SIZE = 100;
  static constexpr int TILE_OFFSET = 100;

  GridStyle() = delete;
};

struct WindowStyle
{
  static constexpr int WIDTH = 600;
  static constexpr int HEIGHT = 600;
  static constexpr int FONT_SIZE = 50;

  WindowStyle() = delete;
};
