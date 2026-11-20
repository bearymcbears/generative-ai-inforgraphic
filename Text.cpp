#include "Text.h"
#include <iostream>
using namespace std;

Text::Text(char *text, int posX, int posY, int w, int h, int fontSize = 16, Color color = BLACK, Font font = GetFontDefault(), bool clickable = 0):
posX(posX), posY(posY), width(w), height(h), fontSize(fontSize), color(color), font(font), text(text), clickable(clickable) {}

void Text::Render() {

    buttonShape = {(float)posX, (float)posY, (float)width, (float)height};

    if (CheckCollisionPointRec(GetMousePosition(), buttonShape) && clickable && !currMoving) {
        DrawRectangleRounded(buttonShape, 0.2f, 4, ColorBrightness(color, -0.1f)); // if mouse is inside button, draw darker button (only works if button is enabled and isn't currently moving)
    }
    else { 
        DrawRectangleRounded(buttonShape, 0.2f, 4, color); // else draw normal button
    }

    float floatPosX =  posX + ((width - MeasureText(text, 16)) / 2);
    float floatPosY =  posY + ((height - 16) / 2);

    DrawTextEx(font, text,
    {floatPosX, floatPosY}, fontSize, 1.0, color);

    clock++;

}

bool Text::Clicked() {
    return CheckCollisionPointRec(GetMousePosition(), buttonShape) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !currMoving && clickable;
}


void Text::MoveX(int start, int moveX, int speed) {

    if (clock >= start && clock < start + (abs(moveX) / speed)) {
        posX += speed * (moveX / abs(moveX));
        currMoving = true;
    }
    else {
        currMoving = false;
    }

}

void Text::MoveY(int start, int moveY, int speed) {

    moveY = -1; // positive y values mean downward movement, this makes it so positive y values mean upward movement

    if (clock >= start && clock < start + (abs(moveY) / speed)) {
        posY += speed + (moveY / abs(moveY));
        currMoving = true;
    }
    else {
        currMoving = false;
    }

}

void Text::Reset() { // reset the button when new screens are displayed
    clock = 0;
    posX = initX;
    posY = initY;
}