#include "Core.h"
#include <iostream>

Grid::Grid(int height, int width)
{
    this->height = height;
    this->width = width;

    CreateGrid();
    InitTiles();
}

Grid::~Grid()
{
}

Tile *Grid::getTile(int x, int y)
{
    int idx = x * width + y;

    if (0 < idx < height * width)
    {
        return &tiles[idx];
    }

    return nullptr;
}

bool Grid::setTile(int x, int y, int value)
{
    Tile *tile = getTile(x, y);
    return setTile(tile, value);
}

bool Grid::setTile(Tile *tile, int value)
{
    if (tile == nullptr)
    {
        return false;
    }

    tile->value = value;

    return true;
}

void Grid::CreateGrid()
{
    tiles = new Tile[height * width];
}

void Grid::InitTiles()
{
    for (int i = 0; i < height * width; i++)
    {
        int y = i / width;
        int x = i % width;

        tiles[i].x = x;
        tiles[i].y = y;
        tiles[i].value = 0;
    }
}

void Grid::MoveRow(int x, Direction dir)
{
    if (dir == Direction::RIGHT)
    {
        int y = width - 1;

        Tile *tile = getTile(x, y);

        // Merge
        while (y > 0)
        {
            Tile *prevTile = getTile(x, y - 1);

            if (prevTile->value != 0)
            {
                if (prevTile->value == tile->value)
                {
                    tile->value++;
                    prevTile->value = 0;
                }
                else
                {
                    tile = prevTile;
                }
            }

            y--;
        }

        // Slide
        int zeroYPos = -1;
        for (int y = width - 1; y >= 0; y--)
        {
            tile = getTile(x, y);
            Tile *zeroTile = getTile(x, zeroYPos);

            if (tile->value == 0 and zeroYPos == -1)
            {
                zeroYPos = y;
            }

            if (tile->value != 0 and zeroYPos != -1)
            {
                zeroTile->value = tile->value;
                tile->value = 0;
                zeroYPos = y;
            }
        }
    }
}

void Grid::Debug()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << getTile(i, j)->value;
        }
        std::cout << std::endl;
    }
}
