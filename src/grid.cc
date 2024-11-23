#include "grid.h"

#include <format>

auto Grid::Rows() const -> size_t
{
    return n_rows;
}

auto Grid::Cols() const -> size_t
{
    return n_cols;
}

void Grid::Init()
{
    for (size_t row = 0; row < n_rows; ++row)
    {
        for (size_t col = 0; col < n_cols; ++col)
        {
            auto &tile = tiles.at(row * n_cols + col);

            tile.row = row;
            tile.col = col;
            tile.value = 0;
        }
    }
}

auto Grid::IsValidPosition(const size_t row, const size_t col) const -> bool
{
    return row < n_rows && col < n_cols;
}

auto Grid::GetTile(const size_t row, const size_t col) -> Tile &
{
    if (!IsValidPosition(row, col))
    {
        const std::string msg = std::format("{} x {} is out of range. Grid size: ({}, {})", row, col, n_rows, n_cols);
        throw std::out_of_range(msg);
    }

    return tiles.at(row * n_cols + col);
}

auto Grid::GetTile(const size_t row, const size_t col) const -> const Tile &
{
    if (!IsValidPosition(row, col))
    {
        const std::string msg = std::format("{} x {} is out of range. Grid size: ({}, {})", row, col, n_rows, n_cols);
        throw std::out_of_range(msg);
    }

    return tiles.at(row * n_cols + col);
}

auto Grid::AdjacentTiles(size_t row, size_t col) const -> std::vector<Tile>
{
    if (!IsValidPosition(row, col))
    {
        const std::string msg = std::format("{} x {} is out of range. Grid size: ({}, {})", row, col, n_rows, n_cols);
        throw std::out_of_range(msg);
    }

    std::vector<Tile> neighbours(4);

    for (const auto &[row_off, col_off] : std::vector<std::pair<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}})
    {
        if (IsValidPosition(row + row_off, col + col_off))
        {
            neighbours.push_back(GetTile(row + row_off, col + col_off));
        }
    }

    return neighbours;
}

void Grid::SetTile(const size_t row, const size_t col, const int value)
{
    GetTile(row, col).value = value;
}

void Grid::SetTile(const Tile &tile, const int value)
{
    SetTile(tile.row, tile.col, value);
}

auto Grid::IsEmpty(const size_t row, const size_t col) -> bool
{
    return GetTile(row, col).value == 0;
}
