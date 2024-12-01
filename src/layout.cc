#include "layout.h"

auto MessageLayout::TotalSize() const -> float
{
    return title_size + subtitle_size + vertical_gap;
}

auto MessageLayout::TitleRect() const -> SDL_FRect
{
    const float total_height = TotalSize();

    SDL_FRect title_rect;
    title_rect.x = rect.x;
    title_rect.y = rect.y + (rect.h - total_height) / 2 - title_size + offset_y;
    title_rect.h = title_size;
    title_rect.w = rect.w;

    return title_rect;
}

auto MessageLayout::SubtitleRect() const -> SDL_FRect
{
    SDL_FRect subtitle_rect;
    subtitle_rect.x = rect.x;
    subtitle_rect.y = rect.y + TotalSize() + title_size + vertical_gap + offset_y;
    subtitle_rect.h = subtitle_size;
    subtitle_rect.w = rect.w;

    return subtitle_rect;
}

auto ScoreBoardLayout::ScoreRect() const -> SDL_FRect
{
    return SDL_FRect(rect.x, rect.y, box_width, box_height);
}

auto ScoreBoardLayout::BestRect() const -> SDL_FRect
{
    return SDL_FRect(rect.x + box_width + middle_gap, rect.y, box_width, box_height);
}

constexpr auto ApplicationLayout::GridSize() const
{
    return static_cast<float>(width) - (pad_x + 10) * 2.0f + 15;
}

auto ApplicationLayout::ScoreBoardRect() const -> SDL_FRect
{
    const auto grid_size = GridSize();
    return SDL_FRect(pad_x, pad_y, grid_size, 80);
}

auto ApplicationLayout::GridRect() const -> SDL_FRect
{
    const auto grid_size = GridSize();
    return SDL_FRect(pad_x, static_cast<float>(height) - grid_size - pad_y - 10, grid_size, grid_size);
}

auto GridLayout::TileRect(const size_t row, const size_t col) const -> SDL_FRect
{
    const auto i = static_cast<float>(col);
    const auto j = static_cast<float>(row);

    SDL_FRect tile_rect;
    tile_rect.x = rect.x + i * tile_size + (i + 1) * tile_gap;
    tile_rect.y = rect.y + j * tile_size + (j + 1) * tile_gap;
    tile_rect.w = tile_size;
    tile_rect.h = tile_size;

    return tile_rect;
}
