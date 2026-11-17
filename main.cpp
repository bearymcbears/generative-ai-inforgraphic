#include <iostream>
#include "raylib.h"
using namespace std;


int main() {

InitWindow(800,600," Generative AI diagram  ");
SetTargetFPS(30);
Color offWhite = { 248, 246, 240, 255 };
Color babyBlue = { 137, 207, 240, 255 };
while (!WindowShouldClose()) {
    ClearBackground(offWhite);
DrawText("AI AND SURVEILLANCE ", 50, 40, 28, BLACK);
BeginDrawing();
DrawRectangleRounded((Rectangle){150, 150, 240, 90}, 0.2f, 4, babyBlue);
DrawText("Criminal Anthropology ", 170,185,14, BLACK);
EndDrawing();
}
    return 0;
}