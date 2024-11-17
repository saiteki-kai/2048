#include <gtest/gtest.h>

#include "../src/grid.h"

void InitRow(Grid &grid, const size_t row, const std::vector<int> &values)
{
    size_t col = 0;

    for (const int value : values)
    {
        grid.SetTile(row, col++, value);
    }
    grid.Debug();
}

void AssertRow(Grid &grid, const size_t row, const std::vector<int> &values)
{
    grid.Debug();
    size_t col = 0;

    for (const int value : values)
    {
        const auto &[_row, _col, v] = grid.GetTile(row, col++);
        ASSERT_EQ(v, value);
    }
}

TEST(TestSlideRow, SlideRowRightEmpty)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {0, 0, 0, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowLeftEmpty)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {0, 0, 0, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightEdges)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 0, 0, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 4});
}

TEST(TestSlideRow, SlideRowLeftEdges)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 0, 0, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightTriple)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {8, 2, 2, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 8, 2, 4});
}

TEST(TestSlideRow, SlideRowLeftTriple)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {8, 2, 2, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {8, 4, 2, 0});
}

TEST(TestSlideRow, SlideRowRightFull)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 2, 2, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 4, 4});
}

TEST(TestSlideRow, SlideRowLeftFull)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 2, 2, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 4, 0, 0});
}

TEST(TestSlideRow, SlideRowRightSingleEdge)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {64, 0, 0, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 64});
}

TEST(TestSlideRow, SlideRowLeftSingleEdge)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {64, 0, 0, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {64, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightSingleMiddle)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {0, 0, 128, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 128});
}

TEST(TestSlideRow, SlideRowLeftSingleMiddle)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {0, 0, 128, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {128, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightMiddleAdjacent)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {0, 256, 256, 0});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 512});
}

TEST(TestSlideRow, SlideRowLeftMiddleAdjacent)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {0, 256, 256, 0});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {512, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightNonAdjacent)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 0, 2, 2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 2, 4});
}

TEST(TestSlideRow, SlideRowLeftNonAdjacent)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 2, 0, 2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 2, 0, 0});
}

TEST(TestSlideRow, SlideRowRightNoMerge)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 4, 8, 16});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideRow, SlideRowLeftNoMerge)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 4, 8, 16});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideRow, SlideRowRightComplex)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 2, 4, 4});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 4, 8});
}

// could be an error in the slide (non-invariant)
TEST(TestSlideRow, SlideRowLeftComplex)
{
    Grid grid(1, 4);
    InitRow(grid, 0, {2, 2, 4, 4});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 8, 0, 0});
}

TEST(TestSlideRow, SlideRowSingleTile)
{
    Grid grid(1, 1);
    InitRow(grid, 0, {2});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {2});

    InitRow(grid, 0, {2});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {2});
}

TEST(TestSlideRow, SlideRowLargeRight)
{
    Grid grid(1, 12);
    InitRow(grid, 0, {2, 0, 0, 2, 4, 4, 8, 16, 2, 4, 4});
    grid.MoveRow(0, Direction::RIGHT);
    AssertRow(grid, 0, {0, 0, 0, 0, 0, 0, 4, 8, 8, 16, 2, 8});
}

TEST(TestSlideRow, SlideRowLargeLeft)
{
    Grid grid(1, 12);
    InitRow(grid, 0, {2, 0, 0, 2, 4, 4, 8, 16, 2, 4, 4});
    grid.MoveRow(0, Direction::LEFT);
    AssertRow(grid, 0, {4, 8, 8, 16, 2, 8, 0, 0, 0, 0, 0, 0});
}

void InitCol(Grid &grid, const size_t col, const std::vector<int> &values)
{
    size_t row = 0;

    for (const int value : values)
    {
        grid.SetTile(row++, col, value);
    }
    grid.Debug();
}

void AssertCol(Grid &grid, const size_t col, const std::vector<int> &values)
{
    grid.Debug();
    size_t row = 0;

    for (const int value : values)
    {
        const auto &[_row, _col, v] = grid.GetTile(row++, col);
        ASSERT_EQ(v, value);
    }
}

TEST(TestSlideCol, SlideColumnDownEmpty)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {0, 0, 0, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnUpEmpty)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {0, 0, 0, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {0, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownEdges)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 0, 0, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 4});
}

TEST(TestSlideCol, SlideColumnUpEdges)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 0, 0, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownTriple)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {8, 2, 2, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 8, 2, 4});
}

TEST(TestSlideCol, SlideColumnUpTriple)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {8, 2, 2, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {8, 4, 2, 0});
}

TEST(TestSlideCol, SlideColumnDownFull)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 2, 2, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 4, 4});
}

TEST(TestSlideCol, SlideColumnUpFull)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 2, 2, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 4, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownSingleEdge)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {64, 0, 0, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 64});
}

TEST(TestSlideCol, SlideColumnUpSingleEdge)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {64, 0, 0, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {64, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownSingleMiddle)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {0, 0, 128, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 128});
}

TEST(TestSlideCol, SlideColumnUpSingleMiddle)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {0, 0, 128, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {128, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownMiddleAdjacent)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {0, 256, 256, 0});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 512});
}

TEST(TestSlideCol, SlideColumnUpMiddleAdjacent)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {0, 256, 256, 0});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {512, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownNonAdjacent)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 0, 2, 2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 2, 4});
}

TEST(TestSlideCol, SlideColumnUpNonAdjacent)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 2, 0, 2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 2, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownNoMerge)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 4, 8, 16});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideCol, SlideColumnUpNoMerge)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 4, 8, 16});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {2, 4, 8, 16});
}

TEST(TestSlideCol, SlideColumnDownComplex)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 2, 4, 4});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 4, 8});
}

TEST(TestSlideCol, SlideColumnUpComplex)
{
    Grid grid(4, 1);
    InitCol(grid, 0, {2, 2, 4, 4});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 8, 0, 0});
}

TEST(TestSlideCol, SlideColumnSingleTile)
{
    Grid grid(1, 1);
    InitCol(grid, 0, {2});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {2});

    InitCol(grid, 0, {2});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {2});
}

TEST(TestSlideCol, SlideColumnLargeDown)
{
    Grid grid(12, 1);
    InitCol(grid, 0, {2, 0, 0, 2, 4, 4, 8, 16, 2, 4, 4});
    grid.MoveCol(0, Direction::DOWN);
    AssertCol(grid, 0, {0, 0, 0, 0, 0, 0, 4, 8, 8, 16, 2, 8});
}

TEST(TestSlideCol, SlideColumnLargeUp)
{
    Grid grid(12, 1);
    InitCol(grid, 0, {2, 0, 0, 2, 4, 4, 8, 16, 2, 4, 4});
    grid.MoveCol(0, Direction::UP);
    AssertCol(grid, 0, {4, 8, 8, 16, 2, 8, 0, 0, 0, 0, 0, 0});
}
