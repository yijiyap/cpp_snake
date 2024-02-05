#include <iostream>
#include <raylib.h>
#include <deque>

Color pink = {255, 179, 203, 255};
Color darkPink = {112, 58, 75, 255};

const int cellSize{30};
const int cellCount{25};

class Dog
{
public:
    std::deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};

    void Draw()
    {
        for (int i=0; i<body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkPink);
        }
    }
};

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food()
    {
        Image image = LoadImage("Sprites/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw() 
    {
      DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);  
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount -1);
        float y = GetRandomValue(0, cellCount -1);
        return Vector2{x, y};
    }
};

int main()
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize*cellCount, cellSize*cellCount, "Dog Snake");
    SetTargetFPS(60);

    Food food = Food();
    Dog dog = Dog();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        // Drawing
        ClearBackground(pink);
        food.Draw();
        dog.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
