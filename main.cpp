#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <deque>

Color pink = {255, 179, 203, 255};
Color darkPink = {112, 58, 75, 255};

const int cellSize{30};
const int cellCount{25};

double lastUpdateTime{0}; // keep track last update time of the dog, to slow down the dog movement time

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    // for (unsigned int i=0; i<deque.size(); i++)
    // {
    //     if (Vector2Equals(deque[i], element))
    //         return true;
    // }
    for (const auto& n : deque)
    {
        if (Vector2Equals(n, element))
            return true;
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime(); // time since the programme started running
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Dog
{
public:
    std::deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction = {1,0};
    bool addSegment = false;

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

    void Update() // move the doggie
    {
        body.push_front(Vector2Add(body[0], direction)); // add it to the front of the doggie
        if (addSegment == true)
        {
            addSegment = false;
        } else
        {
            body.pop_back(); //remove the last part of the doggie
        }
    }

    void Reset()
    {
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        direction = {1,0};
    }
};

class Food 
{
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> dogBody)
    {
        Image image = LoadImage("Sprites/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(dogBody);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw() 
    {
      DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);  
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x,y};
    }

    Vector2 GenerateRandomPos(std::deque<Vector2> dogBody)
    {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, dogBody))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Game 
{
public:
    Dog dog = Dog();
    Food food = Food(dog.body);
    bool running = true;

    void Draw()
    {
        food.Draw();
        dog.Draw();
    }

    void Update()
    {
        if (running)
        {
            dog.Update();
            CheckAtFood();
            CheckAtEdge();
        }
    }

    void CheckAtFood()
    {
        if(Vector2Equals(dog.body[0], food.position)) //[0] because that is the head of the dog
        {
            food.position = food.GenerateRandomPos(dog.body); // change position of food
            dog.addSegment = true;
            // add block to the front of the dog, and also stop the time

        }
    }

    void CheckAtEdge()
    {
        if(dog.body[0].x == cellCount || dog.body[0].x == -1 || dog.body[0].y == cellCount || dog.body[0].y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        dog.Reset();
        food.position = food.GenerateRandomPos(dog.body);
        running = false;
    }

};

int main()
{
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize*cellCount, cellSize*cellCount, "Dog Snake");
    SetTargetFPS(60);

    Game game = Game();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        if (eventTriggered(0.2)) // 
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.dog.direction.y != 1)
        {
            game.dog.direction = {0,-1};
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.dog.direction.y != -1)
        {
            game.dog.direction = {0,1};
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.dog.direction.x != 1)
        {
            game.dog.direction = {-1,0};
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.dog.direction.x != -1)
        {
            game.dog.direction = {1,0};
            game.running = true;
        }

        // Drawing
        ClearBackground(pink);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
