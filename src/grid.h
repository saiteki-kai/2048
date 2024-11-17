#pragma once

#include <array>
#include <cstdint>
#include <random>

struct Tile
{
    size_t row;
    size_t col;
    uint16_t value;
};

enum class Direction : std::int8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

constexpr double PROB_2 = 0.9;
constexpr double PROB_4 = 0.1;

class Grid
{
  private:
    size_t n_rows = 4;
    size_t n_cols = 4;
    std::array<Tile, 16> tiles = {};

  private:
    [[nodiscard]] auto IsValidPosition(size_t row, size_t col) const -> bool;

  public:
    [[nodiscard]] auto Rows() const -> size_t;
    [[nodiscard]] auto Cols() const -> size_t;
    [[nodiscard]] auto GetTile(size_t row, size_t col) const -> const Tile &;
    void Init();
    auto IsEmpty(size_t row, size_t col) -> bool;
    void SetTile(const Tile &tile, int value);
    void SetTile(size_t row, size_t col, int value);
    auto GetTile(size_t row, size_t col) -> Tile &;
    auto MoveRow(size_t row, Direction dir) -> uint8_t;
    auto MoveCol(size_t col, Direction dir) -> uint8_t;
    auto CanMove() -> bool;
    auto SpawnRandomTile() -> bool;
};
