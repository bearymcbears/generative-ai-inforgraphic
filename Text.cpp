#include "Text.h"
#include <iostream>
using namespace std;

Text::Text(char *text, int posX, int posY, int w, int h, int fontSize = 16, Color color = BLACK, Font font = GetFontDefault(), bool clickable = 0) : posX(posX), posY(posY), width(w), height(h), fontSize(fontSize), color(color), font(font), text(text), clickable(clickable) {}

void Text::Render()
{

    buttonShape = {(float)posX, (float)posY, (float)width, (float)height};

    if (CheckCollisionPointRec(GetMousePosition(), buttonShape) && clickable && !currMoving)
    {
        DrawRectangleRounded(buttonShape, 0.2f, 4, ColorBrightness(boxColor, -0.1f)); // if mouse is inside button, draw darker button (only works if button is enabled and isn't currently moving)
    }
    else
    {
        DrawRectangleRounded(buttonShape, 0.2f, 4, boxColor); // else draw normal button
    }

    int numLines = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n')
        {
            numLines++;
        }
    }

    Vector2 textSize = MeasureTextEx(font, text, (float)fontSize, 1.0f);

    Vector2 textPos = {
        posX + (width  - textSize.x) / 2.0f,
        posY + (height - textSize.y) / 2.0f
    };

    DrawTextEx(font, text, textPos, (float)fontSize, 1.0f, color);

    clock++;
}

bool Text::Clicked()
{
    return CheckCollisionPointRec(GetMousePosition(), buttonShape) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !currMoving && clickable;
}

void Text::MoveX(int start, int moveX, int speed)
{

    if (clock >= start && clock < start + (abs(moveX) / speed))
    {
        posX += speed * (moveX / abs(moveX));
        currMoving = true;
    }
    else
    {
        currMoving = false;
    }
}

void Text::MoveY(int start, int moveY, int speed)
{

    moveY = -1; // positive y values mean downward movement, this makes it so positive y values mean upward movement

    if (clock >= start && clock < start + (abs(moveY) / speed))
    {
        posY += speed + (moveY / abs(moveY));
        currMoving = true;
    }
    else
    {
        currMoving = false;
    }
}

void Text::Reset()
{ // reset the button when new screens are displayed
    clock = 0;
    posX = initX;
    posY = initY;
}