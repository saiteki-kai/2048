#pragma once

#include <SDL3/SDL.h>

enum class TextAlignment : uint8_t
{
    Left,
    Center,
    Right,
};

void SetRenderColor(SDL_Renderer *renderer, const SDL_Color &color);

void FillRect(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color);

void AlignTextRect(SDL_FRect &rect, float text_height, float text_width, TextAlignment alignment);