#include "grid.h"

#include <cassert>
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

void Grid::SetTile(const size_t row, const size_t col, const int value)
{
    GetTile(row, col).value = value;
}

void Grid::SetTile(const Tile &tile, const int value)
{
    SetTile(tile.row, tile.col, value);
}

auto Grid::MoveRow(const size_t row, const Direction dir) -> uint8_t
{
    assert(dir == Direction::LEFT || dir == Direction::RIGHT);

    uint8_t score = 0;

    const bool is_right = dir == Direction::RIGHT;
    const size_t start_col = is_right ? n_cols - 1 : 0;
    const size_t end_col = is_right ? 0 : n_cols - 1;
    const int step = is_right ? -1 : 1;

    size_t write_pos = start_col; // Position to write the next non-zero or merged value
    int last_merged_pos = -1;     // Keeps track of the last merge position

    for (size_t col = start_col; col != end_col + step; col += step)
    {
        auto &[_curr_row, _curr_col, curr_value] = GetTile(row, col);

        // skip empty tiles
        if (curr_value == 0)
        {
            continue;
        }

        if (write_pos != start_col)
        {
            auto &[_target_row, _target_col, target_value] = GetTile(row, write_pos - step);

            if (target_value == curr_value && last_merged_pos != write_pos - step)
            {
                curr_value = 0;
                target_value *= 2;
                score += target_value;
                last_merged_pos = static_cast<int>(write_pos - step); // Mark this position as merged

                continue;
            }
        }

        // Slide the tile to the write position
        if (col != write_pos)
        {
            SetTile(row, write_pos, curr_value);
            curr_value = 0;
        }
        write_pos += step; // Advance the write position
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

    size_t write_pos = start_row; // Position to write the next non-zero or merged value
    int last_merged_pos = -1;     // Keeps track of the last merge position

    for (size_t row = start_row; row != end_row + step; row += step)
    {
        auto &[_curr_row, _curr_col, curr_value] = GetTile(row, col);

        // skip empty tiles
        if (curr_value == 0)
        {
            continue;
        }

        if (write_pos != start_row)
        {
            auto &[_target_row, _target_col, target_value] = GetTile(write_pos - step, col);

            if (target_value == curr_value && last_merged_pos != write_pos - step)
            {
                curr_value = 0;
                target_value *= 2;
                score += target_value;
                last_merged_pos = static_cast<int>(write_pos - step); // Mark this position as merged

                continue;
            }
        }

        // Slide the tile to the write position
        if (row != write_pos)
        {
            SetTile(write_pos, col, curr_value);
            curr_value = 0;
        }
        write_pos += step; // Advance the write position
    }

    return score;
}

auto Grid::IsEmpty(const size_t row, const size_t col) -> bool
{
    return GetTile(row, col).value == 0;
}

// TODO: check if there are tiles that can be merged
bool Grid::CanMove()
{
    // for (size_t row = 0; row < n_rows; ++row)
    // {
    //     // check cols
    //     for (size_t col = 0; col < n_cols; ++col)
    //     {
    //     }
    // }
    //
    // for (size_t col = 0; col < n_cols; ++col)
    // {
    //     // check rows
    // }

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
            if (IsEmpty(row, col))
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
