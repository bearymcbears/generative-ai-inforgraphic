#include "Text.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

Text::Text(char *text, int posX, int posY, int w, int h, int fontSize = 16, Color color = BLACK, Font font = GetFontDefault(), bool clickable = 0, Color boxColor) : initX(posX), initY(posY),
posX(posX), posY(posY), width(w), height(h), fontSize(fontSize), color(color), font(font), text(text), clickable(clickable), boxColor(boxColor) {}

void Text::Render() {

    buttonShape = {(float)posX, (float)posY, (float)width, (float)height};

    if (CheckCollisionPointRec(GetMousePosition(), buttonShape) && clickable && !currMoving) {
        DrawRectangleRounded(buttonShape, 0.2f, 4, ColorBrightness(boxColor, -0.1f)); // if mouse is inside button, draw darker button (only works if button is enabled and isn't currently moving)
    }
    else { 
        DrawRectangleRounded(buttonShape, 0.2f, 4, boxColor); // else draw normal button
    }

  if (text != nullptr) {
    // 1. Split text by '\n' into individual lines
    vector<string> lines;
    string current;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lines.push_back(current);
            current.clear();
        } else {
            current += text[i];
        }
    }
    lines.push_back(current);

    int lineSpacing = fontSize + 4; // adjust spacing between lines if needed
    float totalHeight = (float)(lines.size() * lineSpacing);

    // Vertically center the whole block of lines inside the box
    float startY = (height > 0)
        ? posY + (height - totalHeight) / 2.0f
        : (float)posY;

    // 2. Draw each line centered horizontally inside the box
    for (size_t i = 0; i < lines.size(); i++) {
        int lineWidth = MeasureText(lines[i].c_str(), fontSize);
        float lineX = (width > 0)
            ? posX + (width - lineWidth) / 2.0f
            : (float)posX;

        float lineY = startY + i * lineSpacing;
        DrawText(lines[i].c_str(), (int)lineX, (int)lineY, fontSize, color);
    }
}
}

bool Text::Clicked() {
    return CheckCollisionPointRec(GetMousePosition(), buttonShape) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !currMoving && clickable;
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
    posX = initX;
    posY = initY;
}
