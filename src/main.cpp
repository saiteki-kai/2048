#include "Core.h"

int main(int argc, char const *argv[])
{

    Grid grid = Grid(4, 4);
    grid.MoveRow(2, Direction::RIGHT);

    return 0;
}
