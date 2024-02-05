#include <iostream>
#include <raylib.h>

Color pink = {255, 179, 203, 255};
Color darkPink = {112, 58, 75, 255};

const int cellSize{30};
const int cellCount{25};

class Food {
public:
    Vector2 position{5,6};

    void Draw() 
    {
      DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkPink);  
    }
};

int main()
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize*cellCount, cellSize*cellCount, "F1 Snake");
    SetTargetFPS(60);

    Food food = Food();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        // Drawing
        ClearBackground(pink);
        food.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
