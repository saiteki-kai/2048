#include <gtest/gtest.h>

#include "../src/grid.h"

void InitRow(Grid &grid, const size_t row, const std::vector<int> &values)
{
    size_t col = 0;

    for (const int value : values)
    {
        grid.SetTile(row, col++, value);
    }
}

void AssertRow(Grid &grid, const size_t row, const std::vector<int> &values)
{
    size_t col = 0;

    for (const int value : values)
    {
        const auto &[_row, _col, v] = grid.GetTile(row, col++);
        ASSERT_EQ(v, value);
    }
}

void InitCol(Grid &grid, const size_t col, const std::vector<int> &values)
{
    size_t row = 0;

    for (const int value : values)
    {
        grid.SetTile(row++, col, value);
    }
}

void AssertCol(Grid &grid, const size_t col, const std::vector<int> &values)
{
    size_t row = 0;

    for (const int value : values)
    {
        const auto &[_row, _col, v] = grid.GetTile(row++, col);
        ASSERT_EQ(v, value);
    }
}

TEST(TestSlideRow, SlideRowRightEmpty)
{
    Grid grid;
    InitRow(grid, 0, {0, 0, 0, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowLeftEmpty)
{
    Grid grid;
    InitRow(grid, 0, {0, 0, 0, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightEdges)
{
    Grid grid;
    InitRow(grid, 0, {2, 0, 0, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 4});
}

TEST(TestSlideRow, SlideRowLeftEdges)
{
    Grid grid;
    InitRow(grid, 0, {2, 0, 0, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightTriple)
{
    Grid grid;
    InitRow(grid, 0, {8, 2, 2, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 8, 2, 4});
}

TEST(TestSlideRow, SlideRowLeftTriple)
{
    Grid grid;
    InitRow(grid, 0, {8, 2, 2, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {8, 4, 2, 0});
}

TEST(TestSlideRow, SlideRowRightFull)
{
    Grid grid;
    InitRow(grid, 0, {2, 2, 2, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 4, 4});
}

TEST(TestSlideRow, SlideRowLeftFull)
{
    Grid grid;
    InitRow(grid, 0, {2, 2, 2, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 4, 0, 0});
}

TEST(TestSlideRow, SlideRowRightSingleEdge)
{
    Grid grid;
    InitRow(grid, 0, {64, 0, 0, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 64});
}

TEST(TestSlideRow, SlideRowLeftSingleEdge)
{
    Grid grid;
    InitRow(grid, 0, {64, 0, 0, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {64, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightSingleMiddle)
{
    Grid grid;
    InitRow(grid, 0, {0, 0, 128, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 128});
}

TEST(TestSlideRow, SlideRowLeftSingleMiddle)
{
    Grid grid;
    InitRow(grid, 0, {0, 0, 128, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {128, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightMiddleAdjacent)
{
    Grid grid;
    InitRow(grid, 0, {0, 256, 256, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 512});
}

TEST(TestSlideRow, SlideRowLeftMiddleAdjacent)
{
    Grid grid;
    InitRow(grid, 0, {0, 256, 256, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {512, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightNonAdjacent)
{
    Grid grid;
    InitRow(grid, 0, {2, 0, 2, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 2, 4});
}

TEST(TestSlideRow, SlideRowLeftNonAdjacent)
{
    Grid grid;
    InitRow(grid, 0, {2, 2, 0, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 2, 0, 0});
}

TEST(TestSlideRow, SlideRowRightNoMerge)
{
    Grid grid;
    InitRow(grid, 0, {2, 4, 8, 16});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideRow, SlideRowLeftNoMerge)
{
    Grid grid;
    InitRow(grid, 0, {2, 4, 8, 16});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideRow, SlideRowRightComplex)
{
    Grid grid;
    InitRow(grid, 0, {2, 2, 4, 4});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 4, 8});
}

// could be an error in the slide (non-invariant)
TEST(TestSlideRow, SlideRowLeftComplex)
{
    Grid grid;
    InitRow(grid, 0, {2, 2, 4, 4});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 8, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownEmpty)
{
    Grid grid;
    InitCol(grid, 0, {0, 0, 0, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnUpEmpty)
{
    Grid grid;
    InitCol(grid, 0, {0, 0, 0, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownEdges)
{
    Grid grid;
    InitCol(grid, 0, {2, 0, 0, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 4});
}

TEST(TestSlideCol, SlideColumnUpEdges)
{
    Grid grid;
    InitCol(grid, 0, {2, 0, 0, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownTriple)
{
    Grid grid;
    InitCol(grid, 0, {8, 2, 2, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 8, 2, 4});
}

TEST(TestSlideCol, SlideColumnUpTriple)
{
    Grid grid;
    InitCol(grid, 0, {8, 2, 2, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {8, 4, 2, 0});
}

TEST(TestSlideCol, SlideColumnDownFull)
{
    Grid grid;
    InitCol(grid, 0, {2, 2, 2, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 4, 4});
}

TEST(TestSlideCol, SlideColumnUpFull)
{
    Grid grid;
    InitCol(grid, 0, {2, 2, 2, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 4, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownSingleEdge)
{
    Grid grid;
    InitCol(grid, 0, {64, 0, 0, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 64});
}

TEST(TestSlideCol, SlideColumnUpSingleEdge)
{
    Grid grid;
    InitCol(grid, 0, {64, 0, 0, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {64, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownSingleMiddle)
{
    Grid grid;
    InitCol(grid, 0, {0, 0, 128, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 128});
}

TEST(TestSlideCol, SlideColumnUpSingleMiddle)
{
    Grid grid;
    InitCol(grid, 0, {0, 0, 128, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {128, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownMiddleAdjacent)
{
    Grid grid;
    InitCol(grid, 0, {0, 256, 256, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 512});
}

TEST(TestSlideCol, SlideColumnUpMiddleAdjacent)
{
    Grid grid;
    InitCol(grid, 0, {0, 256, 256, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {512, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownNonAdjacent)
{
    Grid grid;
    InitCol(grid, 0, {2, 0, 2, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 2, 4});
}

TEST(TestSlideCol, SlideColumnUpNonAdjacent)
{
    Grid grid;
    InitCol(grid, 0, {2, 2, 0, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 2, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownNoMerge)
{
    Grid grid;
    InitCol(grid, 0, {2, 4, 8, 16});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideCol, SlideColumnUpNoMerge)
{
    Grid grid;
    InitCol(grid, 0, {2, 4, 8, 16});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideCol, SlideColumnDownComplex)
{
    Grid grid;
    InitCol(grid, 0, {2, 2, 4, 4});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 4, 8});
}

TEST(TestSlideCol, SlideColumnUpComplex)
{
    Grid grid;
    InitCol(grid, 0, {2, 2, 4, 4});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 8, 0, 0});
}
