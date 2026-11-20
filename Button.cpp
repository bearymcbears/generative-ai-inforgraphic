#include "Button.h"
#include <iostream>
#include <cmath>
using namespace std;

Button::Button(int posX, int posY, int w, int h, char* txt, bool clickable):posX(posX), posY(posY), width(w), height(h), text(txt), enabled(clickable) {}

void Button::Render() {

    buttonShape = {(float)posX, (float)posY, (float)width, (float)height};

    if (CheckCollisionPointRec(GetMousePosition(), buttonShape) && enabled && !currMoving) {
        DrawRectangleRounded(buttonShape, 0.2f, 4, ColorBrightness(color, -0.1f)); // if mouse is inside button, draw darker button (only works if button is enabled and isn't currently moving)
    }
    else { 
        DrawRectangleRounded(buttonShape, 0.2f, 4, color); // else draw normal button
    }

    DrawText(text,
    posX + ((width - MeasureText(text, 16)) / 2),
    posY + ((height - 16) / 2),
    16, BLACK);

    clock++;

}

bool Button::Clicked() {
    return CheckCollisionPointRec(GetMousePosition(), buttonShape) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !currMoving && enabled;
}


void Button::MoveX(int start, int moveX, int speed) {

    if (clock >= start && clock < start + (abs(moveX) / speed)) {
        posX += speed * (moveX / abs(moveX));
        currMoving = true;
    }
    else {
        currMoving = false;
    }

}

void Button::MoveY(int start, int moveY, int speed) {

    moveY = -1; // positive y values mean downward movement, this makes it so positive y values mean upward movement

    if (clock >= start && clock < start + (abs(moveY) / speed)) {
        posY += speed + (moveY / abs(moveY));
        currMoving = true;
    }
    else {
        currMoving = false;
    }

}

void Button::Reset() { // reset the button when new screens are displayed
    clock = 0;
    posX = initX;
    posY = initY;
}