#include "game.h"

#include <cassert>
#include <iostream>
#include <random>

auto Game::GetGrid() -> Grid &
{
    return grid;
}

void Game::Start()
{
    grid.Init();
    Spawn();
    Spawn();
}

void Game::Reset()
{
    best_score = BestScore();
    score = 0;
    can_move = true;

    Start();
}

void Game::Move(const Direction dir)
{
    int move_score = 0;

    if (dir == Direction::UP or dir == Direction::DOWN)
    {
        for (size_t col = 0; col < grid.Cols(); ++col)
        {
            move_score = MoveCol(col, dir);
        }
    }
    else
    {
        for (size_t row = 0; row < grid.Rows(); ++row)
        {
            move_score += MoveRow(row, dir);
        }
    }

    score += move_score;
}

auto Game::Score() const -> std::uint32_t
{
    return score;
}

auto Game::BestScore() const -> std::uint32_t
{
    if (score > best_score)
    {
        return score;
    }

    return best_score;
}

auto Game::Win() -> bool
{
    for (size_t row = 0; row < grid.Rows(); ++row)
    {
        for (size_t col = 0; col < grid.Cols(); ++col)
        {
            if (grid.GetTile(row, col).value == 2048)
            {
                return true;
            }
        }
    }

    return false;
}

auto Game::Lose() -> bool
{
    for (size_t row = 0; row < grid.Rows(); ++row)
    {
        for (size_t col = 0; col < grid.Cols(); ++col)
        {
            const Tile &tile = grid.GetTile(row, col);

            // there are still moves available
            if (tile.value == 0)
            {
                return false;
            }

            for (const Tile &neigh : grid.AdjacentTiles(row, col))
            {
                if (tile.value == neigh.value)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

auto Game::MoveRow(const size_t row, const Direction dir) -> uint8_t
{
    assert(dir == Direction::LEFT || dir == Direction::RIGHT);

    uint8_t score = 0;

    const bool is_right = dir == Direction::RIGHT;
    const size_t start_col = is_right ? grid.Cols() - 1 : 0;
    const size_t end_col = is_right ? 0 : grid.Cols() - 1;
    const int step = is_right ? -1 : 1;

    size_t write_pos = start_col; // Position to write the next non-zero or merged value
    int last_merged_pos = -1;     // Keeps track of the last merge position

    for (size_t col = start_col; col != end_col + step; col += step)
    {
        auto &[_curr_row, _curr_col, curr_value] = grid.GetTile(row, col);

        // skip empty tiles
        if (curr_value == 0)
        {
            continue;
        }

        if (write_pos != start_col)
        {
            auto &[_target_row, _target_col, target_value] = grid.GetTile(row, write_pos - step);

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
            grid.SetTile(row, write_pos, curr_value);
            curr_value = 0;
        }
        write_pos += step; // Advance the write position
    }

    return score;
}

// Bad Copy from MoveRow (Need Refactoring)
auto Game::MoveCol(const size_t col, const Direction dir) -> uint8_t
{
    assert(dir == Direction::UP || dir == Direction::DOWN);

    uint8_t score = 0;

    const bool is_down = dir == Direction::DOWN;
    const size_t start_row = is_down ? grid.Rows() - 1 : 0;
    const size_t end_row = is_down ? 0 : grid.Rows() - 1;
    const int step = is_down ? -1 : 1;

    size_t write_pos = start_row; // Position to write the next non-zero or merged value
    int last_merged_pos = -1;     // Keeps track of the last merge position

    for (size_t row = start_row; row != end_row + step; row += step)
    {
        auto &[_curr_row, _curr_col, curr_value] = grid.GetTile(row, col);

        // skip empty tiles
        if (curr_value == 0)
        {
            continue;
        }

        if (write_pos != start_row)
        {
            auto &[_target_row, _target_col, target_value] = grid.GetTile(write_pos - step, col);

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
            grid.SetTile(write_pos, col, curr_value);
            curr_value = 0;
        }
        write_pos += step; // Advance the write position
    }

    return score;
}

auto Game::Spawn() -> bool
{
    // get empty tiles
    std::vector<std::pair<size_t, size_t>> empty_tiles;
    empty_tiles.reserve(grid.Rows() * grid.Cols() - 1);

    for (int row = 0; row < grid.Rows(); ++row)
    {
        for (int col = 0; col < grid.Cols(); ++col)
        {
            if (grid.IsEmpty(row, col))
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
    grid.SetTile(rand_row, rand_col, val_dist(gen) == 0 ? 2 : 4);

    return true;
}
