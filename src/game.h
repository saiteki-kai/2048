#pragma once

#include "grid.h"

constexpr double PROB_2 = 0.9;
constexpr double PROB_4 = 0.1;

enum class Direction : std::int8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Game
{
  private:
    Grid grid;
    bool can_move = true;
    std::uint32_t score = 0;
    std::uint32_t best_score = 0;

  public:
    auto GetGrid() -> Grid &;
    void Start();
    void Reset();
    auto Spawn() -> bool;
    void Move(Direction dir);
    auto Win() -> bool;
    auto Lose() -> bool;
    [[nodiscard]] auto Score() const -> std::uint32_t;
    [[nodiscard]] auto BestScore() const -> std::uint32_t;
    auto MoveRow(size_t row, Direction dir) -> uint8_t;
    auto MoveCol(size_t col, Direction dir) -> uint8_t;
};
