#pragma once

#include "grid.h"

class Game
{
  private:
    int rows;
    int cols;
    Grid grid;
    bool can_move = true;
    std::uint32_t score = 0;
    std::uint32_t best_score = 0;

  public:
    Game(int rows, int cols);
    auto GetGrid() -> Grid &;
    void Start();
    void Reset();
    auto CheckWin() -> bool;
    auto CanMove() -> bool;
    void Move(Direction dir);
    auto Spawn() -> bool;
    [[nodiscard]] auto Score() const -> std::uint32_t;
    [[nodiscard]] auto BestScore() const -> std::uint32_t;
};