#include <gtest/gtest.h>

#include "../src/game.h"

void InitRow(Game &game, const size_t row, const std::vector<int> &values)
{
    size_t col = 0;

    for (const int value : values)
    {
        game.GetGrid().SetTile(row, col++, value);
    }
}

void AssertRow(Game &game, const size_t row, const std::vector<int> &values)
{
    size_t col = 0;

    for (const int value : values)
    {
        const auto &[_row, _col, v] = game.GetGrid().GetTile(row, col++);
        ASSERT_EQ(v, value);
    }
}

void InitCol(Game &game, const size_t col, const std::vector<int> &values)
{
    size_t row = 0;

    for (const int value : values)
    {
        game.GetGrid().SetTile(row++, col, value);
    }
}

void AssertCol(Game &game, const size_t col, const std::vector<int> &values)
{
    size_t row = 0;

    for (const int value : values)
    {
        const auto &[_row, _col, v] = game.GetGrid().GetTile(row++, col);
        ASSERT_EQ(v, value);
    }
}

TEST(TestSlideRow, SlideRowRightEmpty)
{
    Game game;
    InitRow(game, 0, {0, 0, 0, 0});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowLeftEmpty)
{
    Game game;
    InitRow(game, 0, {0, 0, 0, 0});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {0, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightEdges)
{
    Game game;
    InitRow(game, 0, {2, 0, 0, 2});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 0, 4});
}

TEST(TestSlideRow, SlideRowLeftEdges)
{
    Game game;
    InitRow(game, 0, {2, 0, 0, 2});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {4, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightTriple)
{
    Game game;
    InitRow(game, 0, {8, 2, 2, 2});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 8, 2, 4});
}

TEST(TestSlideRow, SlideRowLeftTriple)
{
    Game game;
    InitRow(game, 0, {8, 2, 2, 2});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {8, 4, 2, 0});
}

TEST(TestSlideRow, SlideRowRightFull)
{
    Game game;
    InitRow(game, 0, {2, 2, 2, 2});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 4, 4});
}

TEST(TestSlideRow, SlideRowLeftFull)
{
    Game game;
    InitRow(game, 0, {2, 2, 2, 2});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {4, 4, 0, 0});
}

TEST(TestSlideRow, SlideRowRightSingleEdge)
{
    Game game;
    InitRow(game, 0, {64, 0, 0, 0});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 0, 64});
}

TEST(TestSlideRow, SlideRowLeftSingleEdge)
{
    Game game;
    InitRow(game, 0, {64, 0, 0, 0});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {64, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightSingleMiddle)
{
    Game game;
    InitRow(game, 0, {0, 0, 128, 0});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 0, 128});
}

TEST(TestSlideRow, SlideRowLeftSingleMiddle)
{
    Game game;
    InitRow(game, 0, {0, 0, 128, 0});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {128, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightMiddleAdjacent)
{
    Game game;
    InitRow(game, 0, {0, 256, 256, 0});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 0, 512});
}

TEST(TestSlideRow, SlideRowLeftMiddleAdjacent)
{
    Game game;
    InitRow(game, 0, {0, 256, 256, 0});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {512, 0, 0, 0});
}

TEST(TestSlideRow, SlideRowRightNonAdjacent)
{
    Game game;
    InitRow(game, 0, {2, 0, 2, 2});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 2, 4});
}

TEST(TestSlideRow, SlideRowLeftNonAdjacent)
{
    Game game;
    InitRow(game, 0, {2, 2, 0, 2});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {4, 2, 0, 0});
}

TEST(TestSlideRow, SlideRowRightNoMerge)
{
    Game game;
    InitRow(game, 0, {2, 4, 8, 16});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {2, 4, 8, 16});
}

TEST(TestSlideRow, SlideRowLeftNoMerge)
{
    Game game;
    InitRow(game, 0, {2, 4, 8, 16});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {2, 4, 8, 16});
}

TEST(TestSlideRow, SlideRowRightComplex)
{
    Game game;
    InitRow(game, 0, {2, 2, 4, 4});
    game.Move(Direction::RIGHT);
    AssertRow(game, 0, {0, 0, 4, 8});
}

// could be an error in the slide (non-invariant)
TEST(TestSlideRow, SlideRowLeftComplex)
{
    Game game;
    InitRow(game, 0, {2, 2, 4, 4});
    game.Move(Direction::LEFT);
    AssertRow(game, 0, {4, 8, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownEmpty)
{
    Game game;
    InitCol(game, 0, {0, 0, 0, 0});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnUpEmpty)
{
    Game game;
    InitCol(game, 0, {0, 0, 0, 0});
    game.Move(Direction::UP);
    AssertCol(game, 0, {0, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownEdges)
{
    Game game;
    InitCol(game, 0, {2, 0, 0, 2});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 0, 4});
}

TEST(TestSlideCol, SlideColumnUpEdges)
{
    Game game;
    InitCol(game, 0, {2, 0, 0, 2});
    game.Move(Direction::UP);
    AssertCol(game, 0, {4, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownTriple)
{
    Game game;
    InitCol(game, 0, {8, 2, 2, 2});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 8, 2, 4});
}

TEST(TestSlideCol, SlideColumnUpTriple)
{
    Game game;
    InitCol(game, 0, {8, 2, 2, 2});
    game.Move(Direction::UP);
    AssertCol(game, 0, {8, 4, 2, 0});
}

TEST(TestSlideCol, SlideColumnDownFull)
{
    Game game;
    InitCol(game, 0, {2, 2, 2, 2});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 4, 4});
}

TEST(TestSlideCol, SlideColumnUpFull)
{
    Game game;
    InitCol(game, 0, {2, 2, 2, 2});
    game.Move(Direction::UP);
    AssertCol(game, 0, {4, 4, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownSingleEdge)
{
    Game game;
    InitCol(game, 0, {64, 0, 0, 0});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 0, 64});
}

TEST(TestSlideCol, SlideColumnUpSingleEdge)
{
    Game game;
    InitCol(game, 0, {64, 0, 0, 0});
    game.Move(Direction::UP);
    AssertCol(game, 0, {64, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownSingleMiddle)
{
    Game game;
    InitCol(game, 0, {0, 0, 128, 0});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 0, 128});
}

TEST(TestSlideCol, SlideColumnUpSingleMiddle)
{
    Game game;
    InitCol(game, 0, {0, 0, 128, 0});
    game.Move(Direction::UP);
    AssertCol(game, 0, {128, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownMiddleAdjacent)
{
    Game game;
    InitCol(game, 0, {0, 256, 256, 0});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 0, 512});
}

TEST(TestSlideCol, SlideColumnUpMiddleAdjacent)
{
    Game game;
    InitCol(game, 0, {0, 256, 256, 0});
    game.Move(Direction::UP);
    AssertCol(game, 0, {512, 0, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownNonAdjacent)
{
    Game game;
    InitCol(game, 0, {2, 0, 2, 2});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 2, 4});
}

TEST(TestSlideCol, SlideColumnUpNonAdjacent)
{
    Game game;
    InitCol(game, 0, {2, 2, 0, 2});
    game.Move(Direction::UP);
    AssertCol(game, 0, {4, 2, 0, 0});
}

TEST(TestSlideCol, SlideColumnDownNoMerge)
{
    Game game;
    InitCol(game, 0, {2, 4, 8, 16});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {2, 4, 8, 16});
}

TEST(TestSlideCol, SlideColumnUpNoMerge)
{
    Game game;
    InitCol(game, 0, {2, 4, 8, 16});
    game.Move(Direction::UP);
    AssertCol(game, 0, {2, 4, 8, 16});
}

TEST(TestSlideCol, SlideColumnDownComplex)
{
    Game game;
    InitCol(game, 0, {2, 2, 4, 4});
    game.Move(Direction::DOWN);
    AssertCol(game, 0, {0, 0, 4, 8});
}

TEST(TestSlideCol, SlideColumnUpComplex)
{
    Game game;
    InitCol(game, 0, {2, 2, 4, 4});
    game.Move(Direction::UP);
    AssertCol(game, 0, {4, 8, 0, 0});
}
