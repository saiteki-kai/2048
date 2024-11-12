#include "../src/Core.h"
#include <gtest/gtest.h>

void initRow(Grid &grid, int row, const std::vector<int> &values)
{
  int col = 0;

  for (int value : values)
  {
    grid.setTile(0, col++, value);
  }
}

void assertRow(Grid &grid, int row, const std::vector<int> &values)
{
  int col = 0;

  for (int value : values)
  {
    Tile *tile = grid.getTile(0, col++);
    ASSERT_EQ(tile->value, value);
  }
}

TEST(TestSlide, SlideRow2002)
{
  Grid grid(1, 4);
  initRow(grid, 0, {1, 0, 0, 1}); // 2 0 0 2
  grid.MoveRow(0, Direction::RIGHT);
  assertRow(grid, 0, {0, 0, 0, 2}); // 0 0 0 4
}

TEST(TestSlide, SlideRow8222)
{
  Grid grid(1, 4);
  initRow(grid, 0, {3, 1, 1, 1}); // 8 2 2 2
  grid.MoveRow(0, Direction::RIGHT);
  assertRow(grid, 0, {0, 3, 1, 2}); // 0 8 2 4
}

TEST(TestSlide, SlideRow2222)
{
  Grid grid(1, 4);
  initRow(grid, 0, {1, 1, 1, 1}); // 2 2 2 2
  grid.MoveRow(0, Direction::RIGHT);
  assertRow(grid, 0, {0, 0, 2, 2}); // 0 0 4 4
}

TEST(TestSlide, SlideRow8000)
{
  Grid grid(1, 4);
  initRow(grid, 0, {8, 0, 0, 0}); // 64 0 0 0
  grid.MoveRow(0, Direction::RIGHT);
  assertRow(grid, 0, {0, 0, 0, 8}); // 0 0 0 64
}

TEST(TestSlide, SlideRow0090)
{
  Grid grid(1, 4);
  initRow(grid, 0, {0, 0, 9, 0}); // 0 0 128 0
  grid.MoveRow(0, Direction::RIGHT);
  assertRow(grid, 0, {0, 0, 0, 9}); // 0 0 0 128
}

TEST(TestSlide, SlideRow0990)
{
  Grid grid(1, 4);
  initRow(grid, 0, {0, 9, 9, 0}); // 0 0 256 0
  grid.MoveRow(0, Direction::RIGHT);
  assertRow(grid, 0, {0, 0, 0, 10}); // 0 0 0 256
}
