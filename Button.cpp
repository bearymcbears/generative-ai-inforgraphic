#include "Button.h"
#include <iostream>
using namespace std;

Button::Button(int x, int y, int w, int h, char* txt) {
    posX = x;
    posY = y;
    width = w;
    height = h;
    text = txt;
    buttonShape = {(float)posX, (float)posY, (float)width, (float)height};
}

void Button::Render() {

    if (CheckCollisionPointRec(GetMousePosition(), buttonShape)) {
        DrawRectangleRounded(buttonShape, 0.2f, 4, ColorBrightness(color, -0.1f)); // if mouse is inside button, draw darker button
    }
    else { 
        DrawRectangleRounded(buttonShape, 0.2f, 4, color); // else draw normal button
    }

    DrawText(text,
    posX + ((width - MeasureText(text, 16)) / 2),
    posY + ((height - 16) / 2),
    16, BLACK); 

}

bool Button::Clicked() {
    return CheckCollisionPointRec(GetMousePosition(), buttonShape) && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

