#include "grid.h"

#include <cassert>
#include <format>
#include <random>

Grid::Grid(const size_t rows, const size_t cols) : n_rows(rows), n_cols(cols), tiles(rows, std::vector<Tile>(cols))
{
    InitTiles();
}

auto Grid::CheckPosition(const size_t row, const size_t col) const -> bool
{
    return row < n_rows && col < n_cols;
}

auto Grid::GetSize() const -> Size
{
    return Size(n_rows, n_cols);
}

auto Grid::GetTile(const size_t row, const size_t col) -> Tile &
{
    if (!CheckPosition(row, col))
    {
        const std::string msg =
            std::format("{} x {} is out of range. The grid size is ({}, {})", row, col, n_rows, n_cols);

        throw std::out_of_range(msg);
    }

    return tiles[row][col];
}

void Grid::SetTile(Tile &tile, const size_t row, const size_t col, const int value) const
{
    if (!CheckPosition(row, col))
    {
        throw std::out_of_range("Grid::setTile");
    }

    tile.row = row;
    tile.col = col;
    tile.value = value;
}

void Grid::SetTile(const size_t row, const size_t col, const int value)
{
    GetTile(row, col).value = value;
}

void Grid::SetTile(const Tile &tile, const int value)
{
    return SetTile(tile.row, tile.col, value);
}

void Grid::InitTiles()
{
    for (size_t row = 0; row < n_rows; ++row)
    {
        for (size_t col = 0; col < n_cols; ++col)
        {
            SetTile(tiles[row][col], row, col, 0);
        }
    }
}

auto Grid::MoveRow(const size_t row, const Direction dir) -> uint8_t
{
    assert(dir == Direction::LEFT || dir == Direction::RIGHT);

    uint8_t score = 0;

    const bool is_right = dir == Direction::RIGHT;
    const size_t start_col = is_right ? n_cols - 1 : 0;
    const size_t end_col = is_right ? 0 : n_cols - 1;
    const int step = is_right ? -1 : 1;

    size_t curr_col = start_col;

    if (start_col == end_col)
    {
        return 0;
    }

    // Merge
    for (size_t col = start_col; col != end_col - step; col += step)
    {
        auto &[_curr_row, _curr_col, curr_value] = GetTile(row, curr_col);
        auto &[_prev_row, _prev_col, prev_value] = GetTile(row, col + step);

        if (curr_value == 0)
        {
            curr_col = col + step;
            continue;
        }

        if (prev_value == 0)
        {
            continue;
        }

        if (curr_value == prev_value)
        {
            curr_value *= 2;
            prev_value = 0;

            curr_col = col;

            score += curr_value;
        }
        else
        {
            curr_col = col + step;
        }
    }

    // Slide
    int zero_col_pos = -1;
    for (size_t col = start_col; col != end_col + step; col += step)
    {
        Tile &curr_tile = GetTile(row, col);

        if (curr_tile.value == 0 && zero_col_pos == -1)
        {
            zero_col_pos = static_cast<int>(col);
        }

        if (curr_tile.value != 0 && zero_col_pos != -1)
        {
            Tile &zero_tile = GetTile(row, zero_col_pos);
            zero_tile.value = curr_tile.value;
            curr_tile.value = 0;
            zero_col_pos = static_cast<int>(col); // current position is now a 0
        }
    }

    return score;
}

// Bad Copy from MoveRow (Need Refactoring)
auto Grid::MoveCol(const size_t col, const Direction dir) -> uint8_t
{
    assert(dir == Direction::UP || dir == Direction::DOWN);

    uint8_t score = 0;

    const bool is_down = dir == Direction::DOWN;
    const size_t start_row = is_down ? n_rows - 1 : 0;
    const size_t end_row = is_down ? 0 : n_rows - 1;
    const int step = is_down ? -1 : 1;

    size_t curr_row = start_row;

    if (start_row == end_row)
    {
        return 0;
    }

    // Merge
    for (size_t row = start_row; row != end_row - step; row += step)
    {
        auto &[_curr_row, _curr_col, curr_value] = GetTile(curr_row, col);
        auto &[_prev_row, _prev_col, prev_value] = GetTile(row + step, col);

        if (curr_value == 0)
        {
            curr_row = row + step;
            continue;
        }

        if (prev_value == 0)
        {
            continue;
        }

        if (curr_value == prev_value)
        {
            curr_value *= 2;
            prev_value = 0;

            curr_row = row;

            score += curr_value;
        }
        else
        {
            curr_row = row + step;
        }
    }

    // Slide
    int zero_row_pos = -1;
    for (size_t row = start_row; row != end_row + step; row += step)
    {
        Tile &curr_tile = GetTile(row, col);

        if (curr_tile.value == 0 && zero_row_pos == -1)
        {
            zero_row_pos = static_cast<int>(row);
        }

        if (curr_tile.value != 0 && zero_row_pos != -1)
        {
            Tile &zero_tile = GetTile(zero_row_pos, col);
            zero_tile.value = curr_tile.value;
            curr_tile.value = 0;
            zero_row_pos = static_cast<int>(row); // current position is now a 0
        }
    }

    return score;
}

auto Grid::IsEmpty(const size_t row, const size_t col) -> bool
{
    return GetTile(row, col).value == 0;
}

auto Grid::IsEmpty(const Tile &tile) -> bool
{
    return tile.value == 0;
}

bool Grid::CanMove()
{
    // TODO: check if there are tiles that can be merged
    return true;
}

auto Grid::SpawnRandomTile() -> bool
{
    // get empty tiles
    std::vector<std::pair<size_t, size_t>> empty_tiles;
    empty_tiles.reserve(n_rows * n_cols - 1);

    for (int row = 0; row < n_rows; ++row)
    {
        for (int col = 0; col < n_cols; ++col)
        {
            if (IsEmpty(GetTile(row, col)))
            {
                empty_tiles.emplace_back(row, col);
            }
        }
    }

    if (empty_tiles.empty())
    {
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> index_dist(0, empty_tiles.size() - 1);

    // get random empty tile
    const size_t randomIdx = index_dist(gen);
    const auto &[rand_row, rand_col] = empty_tiles[randomIdx];

    std::discrete_distribution val_dist({PROB_2, PROB_4});

    // spawn random tile
    SetTile(rand_row, rand_col, val_dist(gen) == 0 ? 2 : 4);

    return true;
}
