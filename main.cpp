#include "src/app.h"

auto main(int argc, char **argv) -> int
{
    auto app = Application(4, 1);
    app.Run();
}
