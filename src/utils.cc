#include "utils.h"

#include <SDL3/SDL_render.h>

void SetRenderColor(SDL_Renderer *renderer, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void FillRect(SDL_Renderer *renderer, const SDL_FRect *rect, const SDL_Color &color)
{
    SetRenderColor(renderer, color);
    SDL_RenderFillRect(renderer, rect);
}

void AlignTextRect(SDL_FRect &rect, const float text_height, const float text_width, const TextAlignment alignment)
{
    switch (alignment)
    {
    case TextAlignment::Left:
        break;
    case TextAlignment::Right:
        rect.x = rect.x + rect.w - text_width;
        break;
    case TextAlignment::Center:
    default:
        rect.x = rect.x + (rect.w - text_width) / 2;
        break;
    }
    rect.y = rect.y + (rect.h - text_height) / 2;
    rect.h = text_height;
    rect.w = text_width;
}
