#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

struct Tile
{
    size_t row;
    size_t col;
    uint16_t value;
};

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
    [[nodiscard]] auto AdjacentTiles(size_t row, size_t col) const -> std::vector<Tile>;
    void Init();
    auto IsEmpty(size_t row, size_t col) -> bool;
    void SetTile(const Tile &tile, int value);
    void SetTile(size_t row, size_t col, int value);
    auto GetTile(size_t row, size_t col) -> Tile &;
};
