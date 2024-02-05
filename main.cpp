#include <iostream>
#include <raylib.h>

Color pink = {255, 179, 203, 255};
Color darkPink = {125, 87, 99, 255}

int main()
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(750, 750, "F1 Snake");
    SetTargetFPS(60);

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        // Drawing
        ClearBackground(pink);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
