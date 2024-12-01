#pragma once

#include "grid.h"

#include <random>

constexpr double PROB_2 = 0.9;
constexpr double PROB_4 = 0.1;
constexpr int WIN_TILE = 2048;

enum class Direction : std::int8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class GameState : uint8_t
{
    Startup,
    GameOver,
    Playing,
    Victory,
};

struct Game
{
  private:
    Grid grid;
    std::uint32_t score = 0;
    std::uint32_t best_score = 0;
    GameState state = GameState::Startup;
    std::mt19937 gen;

  private:
    auto Spawn() -> bool;
    auto CheckVictory() -> bool;
    auto CheckGameOver() -> bool;
    auto MoveRow(size_t row, Direction dir) -> uint8_t;
    auto MoveCol(size_t col, Direction dir) -> uint8_t;

  public:
    Game();
    auto GetGrid() -> Grid &;
    void Start();
    void Reset();
    void Move(Direction dir);
    auto Update() -> bool;
    [[nodiscard]] auto Score() const -> std::uint32_t;
    [[nodiscard]] auto BestScore() const -> std::uint32_t;
    [[nodiscard]] auto State() const -> GameState;
};
