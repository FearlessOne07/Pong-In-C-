#include <raylib.h>
#include <iostream>
using namespace std;

#ifndef BALL_H
#define BALL_H
int player_score;
int cpu_score;

// Colors
Color green = Color{38, 185, 154, 255};
Color dark_green = Color{20, 160, 133, 255};
Color light_green = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};

class Ball
{
public:
    float x, y;
    int radius;
    int speed_x, speed_y;

    void draw()
    {
        DrawCircle(x, y, radius, yellow);
    }

    void update()
    {
        x += speed_x;
        y += speed_y;
        ;

        if (x + radius >= GetScreenWidth())
        {
            player_score++;
            restPosition();
        }

        if (x - radius <= 0)
        {
            ++cpu_score;
            restPosition();
        }

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
    }

    void restPosition()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2]{-1, 1};

        speed_y *= speed_choices[GetRandomValue(0, 1)];
        speed_x *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Player
{
protected:
    void boundaries()
    {

        if (y <= 0)
        {
            y = 0;
        }

        if ((y + heigth) >= GetScreenHeight())
        {
            y = GetScreenHeight() - heigth;
        }
    }

public:
    float x, y;
    int speed_y;
    float width, heigth;

    void draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, heigth}, 0.8, 0, WHITE);
    }

    void update()
    {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            y -= speed_y;
        }

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            y += speed_y;
        }

        boundaries();
    }
};

class CpuPaddle : public Player
{
public:
    void update(int ball_y)
    {
        if (y + heigth / 2 > ball_y)
        {
            y -= speed_y;
        }

        if (y + heigth / 2 <= ball_y)
        {
            y += speed_y;
        }

        boundaries();
    }
};

#endif