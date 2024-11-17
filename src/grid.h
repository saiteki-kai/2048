#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

struct Tile
{
    size_t row;
    size_t col;
    int value;
};

struct Size
{
    size_t width;
    size_t height;
};

enum Direction : std::int8_t
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
    size_t n_rows;
    size_t n_cols;
    std::vector<std::vector<Tile>> tiles;

  private:
    [[nodiscard]] auto CheckPosition(size_t row, size_t col) const -> bool;

  public:
    Grid(size_t rows, size_t cols);
    auto GetTile(size_t row, size_t col) -> Tile &;
    void SetTile(Tile &tile, size_t row, size_t col, int value) const;
    void SetTile(const Tile &tile, int value);
    void SetTile(size_t row, size_t col, int value);
    static auto IsEmpty(const Tile &tile) -> bool;
    auto IsEmpty(size_t row, size_t col) -> bool;
    [[nodiscard]] auto GetSize() const -> Size;
    void InitTiles();
    auto SpawnRandomTile() -> bool;
    auto CanMove() -> bool;
    auto MoveRow(size_t row, Direction dir) -> uint8_t;
    auto MoveCol(size_t col, Direction dir) -> uint8_t;
    auto Debug()
    {
        for (size_t x = 0; x < n_rows; ++x)
        {
            for (size_t y = 0; y < n_cols; ++y)
            {
                Tile *tile = &tiles[x][y];
                // std::cout << std::format("{},{}: x:{}, y:{}, value:{}", x, y,
                // tile->x, tile->y, tile->value);
                std::cout << tile->value << " ";
            }
            std::cout << "\n";
        }
    }
};
