#include <gtest/gtest.h>

#include "../src/grid.h"

class GridTest : public ::testing::Test
{
  public:
    Grid grid;

    void SetUp() override
    {
        grid.Init();
    }
};

TEST_F(GridTest, Init)
{
    for (size_t row = 0; row < grid.Rows(); ++row)
    {
        for (size_t col = 0; col < grid.Cols(); ++col)
        {
            auto &[x, y, value] = grid.GetTile(row, col);
            ASSERT_EQ(x, row);
            ASSERT_EQ(y, col);
            EXPECT_EQ(value, 0);
        }
    }
}

TEST_F(GridTest, CheckDimensions)
{
    EXPECT_EQ(grid.Rows(), 4);
    EXPECT_EQ(grid.Cols(), 4);
}

TEST_F(GridTest, GetTile)
{
    const Tile &tile = grid.GetTile(1, 2);
    EXPECT_EQ(tile.row, 1);
    EXPECT_EQ(tile.col, 2);
    EXPECT_EQ(tile.value, 0);
}

TEST_F(GridTest, GetConstTile)
{
    const Grid const_grid = grid;

    const Tile &tile = const_grid.GetTile(1, 2);
    EXPECT_EQ(tile.row, 1);
    EXPECT_EQ(tile.col, 2);
    EXPECT_EQ(tile.value, 0);

    ASSERT_THROW((void)const_grid.GetTile(5, 5), std::out_of_range);
}

TEST_F(GridTest, CheckPositions)
{
    ASSERT_NO_THROW(grid.GetTile(0, 0));
    ASSERT_THROW(grid.GetTile(0, 4), std::out_of_range);
    ASSERT_THROW(grid.GetTile(4, 0), std::out_of_range);
    ASSERT_THROW(grid.GetTile(4, 4), std::out_of_range);
    ASSERT_THROW(grid.GetTile(5, 5), std::out_of_range);
}

TEST_F(GridTest, IsEmpty)
{
    EXPECT_TRUE(grid.IsEmpty(0, 0));
    grid.SetTile(0, 0, 2);
    EXPECT_FALSE(grid.IsEmpty(0, 0));
}

TEST_F(GridTest, SetTileValue)
{
    grid.SetTile(0, 0, 2);
    EXPECT_EQ(grid.GetTile(0, 0).value, 2);
}

TEST_F(GridTest, SetTileByObject)
{
    const auto &tile = Tile{1, 1, 4};
    grid.SetTile(tile, tile.value);
    EXPECT_EQ(grid.GetTile(1, 1).value, 4);
}

TEST_F(GridTest, GetTileByObject)
{
    const auto &tile = Tile{1, 1, 4};
    grid.SetTile(tile, tile.value);
    EXPECT_EQ(grid.GetTile(1, 1).value, tile.value);
}

void CheckAdjacentTiles(Grid &grid, const size_t row, const size_t col, const std::vector<Tile> &expected_neighbours)
{
    for (auto &[row, col, value] : expected_neighbours)
    {
        grid.SetTile(row, col, value);
    }

    const std::vector<Tile> neighs = grid.AdjacentTiles(row, col);
    ASSERT_EQ(neighs.size(), expected_neighbours.size());

    for (auto &neigh : neighs)
    {
        auto it = std::ranges::find_if(expected_neighbours, [&neigh](const auto &exp_neigh) {
            return exp_neigh.row == neigh.row && exp_neigh.col == neigh.col && exp_neigh.value == neigh.value;
        });
        ASSERT_NE(it, expected_neighbours.end());
    }
}

TEST_F(GridTest, CheckAdjacentCenter)
{
    const std::vector<Tile> expected_neighs = {
        {1, 2, 2}, // Top
        {2, 1, 4}, // Left
        {2, 3, 8}, // Right
        {3, 2, 16} // Bottom
    };

    CheckAdjacentTiles(grid, 2, 2, expected_neighs);
}

TEST_F(GridTest, CheckAdjacentCorner)
{
    const std::vector<Tile> expected_neighs = {
        {0, 1, 2}, // Right
        {1, 0, 4}, // Bottom
    };

    for (auto &[row, col, value] : expected_neighs)
    {
        grid.SetTile(row, col, value);
    }

    CheckAdjacentTiles(grid, 0, 0, expected_neighs);
}

TEST_F(GridTest, CheckAdjacentRightEdge)
{
    const std::vector<Tile> expected_neighs = {
        {1, 3, 2}, // Up
        {3, 3, 4}, // Bottom
        {2, 2, 8}  // Left
    };

    CheckAdjacentTiles(grid, 2, 3, expected_neighs);
}

TEST_F(GridTest, CheckAdjacentInvalid)
{
    ASSERT_THROW((void)grid.AdjacentTiles(9, 9), std::out_of_range);
}