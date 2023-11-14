#include <iostream>
#include <raylib.h>
#include "ball.h"

// Colors

int main(void)
{
    const int SCREEN_W = 1280;
    const int SCREEN_H = 720;
    InitWindow(SCREEN_W, SCREEN_H, "Pong");
    SetTargetFPS(60);

    Ball ball;
    Player player;
    CpuPaddle cpu;

    // Ball
    ball.radius = 20;
    ball.x = SCREEN_W / 2;
    ball.y = SCREEN_H / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    // Player
    player.width = 25;
    player.heigth = 120;
    player.x = 10;
    player.y = (SCREEN_H / 2) - (player.heigth / 2);
    player.speed_y = 6;

    // CPU
    cpu.width = 25;
    cpu.heigth = 120;
    cpu.x = SCREEN_W - 45;
    cpu.y = (SCREEN_H / 2) - 60;
    cpu.speed_y = 6;

    while (WindowShouldClose() == false)
    {

        // Entity Updates
        ball.update();
        player.update();
        cpu.update(ball.y);

        // Drawing
        BeginDrawing();
        ClearBackground(dark_green);
        DrawRectangle(SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, green);
        DrawCircle(SCREEN_W / 2, SCREEN_H / 2, 150, light_green);
        DrawLine(SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H, WHITE);
        ball.draw();
        player.draw();
        cpu.draw();

        DrawText(TextFormat("%i", cpu_score), 3 * GetScreenWidth() / 4, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), GetScreenWidth() / 4, 20, 80, WHITE);
        EndDrawing();

        // Collision Detection

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.heigth}))
        {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.heigth}))
        {
            ball.speed_x *= -1;
        }
    }

    CloseWindow();
}
