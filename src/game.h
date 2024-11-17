#pragma once

#include "grid.h"

enum class Direction : std::int8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

constexpr double PROB_2 = 0.9;
constexpr double PROB_4 = 0.1;

class Game
{
  private:
    Grid grid;
    size_t rows = 0;
    size_t cols = 0;
    bool can_move = true;
    std::uint32_t score = 0;
    std::uint32_t best_score = 0;

  public:
    Game();
    auto GetGrid() -> Grid &;
    void Start();
    void Reset();
    auto CheckWin() -> bool;
    void Move(Direction dir);
    auto Spawn() -> bool;
    [[nodiscard]] auto Score() const -> std::uint32_t;
    [[nodiscard]] auto BestScore() const -> std::uint32_t;
    auto MoveRow(size_t row, Direction dir) -> uint8_t;
    auto MoveCol(size_t col, Direction dir) -> uint8_t;
    auto CanMove() -> bool;
    auto SpawnRandomTile() -> bool;
};
