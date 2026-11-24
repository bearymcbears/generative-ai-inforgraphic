#include "Text.h"
#include <cmath>
#include <vector>
#include <string>

using namespace std;

Text::Text(char *text, int posX, int posY, int w, int h, int fontSize, Color color, Font font, bool clickable, Color boxColor)
    : posX(posX),
      posY(posY),
      initX(posX),
      initY(posY),
      width(w),
      height(h),
      fontSize(fontSize),
      color(color),
      font(font),
      text(text),
      clickable(clickable),
      boxColor(boxColor) {}

void Text::Render() {
    buttonShape = { (float)posX, (float)posY, (float)width, (float)height };

    if (CheckCollisionPointRec(GetMousePosition(), buttonShape) && clickable && !currMoving) {
        DrawRectangleRounded(buttonShape, 0.2f, 4, ColorBrightness(boxColor, -0.1f));
    } else {
        DrawRectangleRounded(buttonShape, 0.2f, 4, boxColor);
    }

    if (text != nullptr) {
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

        int lineSpacing = fontSize + 4;
        float totalHeight = (float)(lines.size() * lineSpacing);

        float startY = (height > 0)
            ? posY + (height - totalHeight) / 2.0f
            : (float)posY;

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
    return CheckCollisionPointRec(GetMousePosition(), buttonShape) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
           !currMoving &&
           clickable;
}

void Text::MoveX(int start, int moveX, int speed) {
    if (speed == 0 || moveX == 0) {
        currMoving = false;
        return;
    }

    int dirX = (moveX > 0) ? 1 : -1;
    int steps = std::abs(moveX) / speed;

    if (clock >= start && clock < start + steps) {
        posX += speed * dirX;
        currMoving = true;
    } else {
        currMoving = false;
    }
}

void Text::MoveY(int start, int moveY, int speed) {
    if (speed == 0 || moveY == 0) {
        currMoving = false;
        return;
    }

    int dirY = (moveY > 0) ? -1 : 1;
    int steps = std::abs(moveY) / speed;

    if (clock >= start && clock < start + steps) {
        posY += speed * dirY;
        currMoving = true;
    } else {
        currMoving = false;
    }
}

void Text::Reset() {
    clock = 0;
    posX = initX;
    posY = initY;
    currMoving = false;
}
