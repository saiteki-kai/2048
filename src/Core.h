#include <iostream>

struct Tile
{
    int x;
    int y;
    int value; // power of the value of the tile (i.e. 0 is empty, 1 is 2, ..., 11 is 2048)
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Grid
{
private:
    Tile *tiles;
    int height;
    int width;

public:
    Grid(int height, int width);
    ~Grid();
    Tile *getTile(int x, int y);
    bool setTile(int x, int y, int value);
    bool setTile(Tile *tile, int value);
    void CreateGrid();
    void InitTiles();
    void MoveRow(int x, Direction dir);
    void Debug();
};
