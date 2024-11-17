#include "game.h"

Game::Game(const int rows, const int cols) : rows(rows), cols(cols), grid(rows, cols)
{
    Start();
}

auto Game::GetGrid() -> Grid &
{
    return grid;
}

void Game::Start()
{
    grid.InitTiles();
    grid.SpawnRandomTile();
    grid.SpawnRandomTile();
}

void Game::Reset()
{
    if (score > best_score)
    {
        best_score = score;
    }
    score = 0;
    can_move = true;

    Start();
}

void Game::Move(const Direction dir)
{
    int move_score = 0;

    if (dir == Direction::UP or dir == Direction::DOWN)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            move_score = grid.MoveCol(col, dir);
        }
    }
    else
    {
        for (size_t row = 0; row < rows; ++row)
        {
            move_score += grid.MoveRow(row, dir);
        }
    }

    score += move_score;
    can_move = move_score != 0;
}

auto Game::Spawn() -> bool
{
    return grid.SpawnRandomTile();
}

auto Game::Score() const -> std::uint32_t
{
    return score;
}

auto Game::BestScore() const -> std::uint32_t
{
    return best_score;
}

auto Game::CheckWin() -> bool
{
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            if (grid.GetTile(row, col).value == 2048)
            {
                return true;
            }
        }
    }

    return false;
}

auto Game::CanMove() -> bool
{
    return can_move; // TODO: check if it's correct
}
