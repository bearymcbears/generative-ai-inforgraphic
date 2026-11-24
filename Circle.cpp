#include "Circle.h"

Circle::Circle(const char *text, int x, int y, int r, int fontsize, Color color, Font font, bool clickable)
    : posX(x),
      posY(y),
      radius(r),
      fontsize(fontsize),
      color(color),
      font(font),
      text(text),
      clickable(clickable),
      Moving(false) {}

void Circle::Render() {
    DrawCircle(posX, posY, radius, color);

    if (CheckCollisionPointCircle(GetMousePosition(), {static_cast<float>(posX), static_cast<float>(posY)}, radius) && clickable) {
        DrawCircle(posX, posY, radius, ColorBrightness(color, -0.1f));
    } else {
        DrawCircle(posX, posY, radius, color);
    }

    if (text == nullptr || text[0] == '\0') return;

    Font activeFont = (font.baseSize > 0) ? font : GetFontDefault();
    float spacing = 1.0f;
    Vector2 textSize = MeasureTextEx(activeFont, text, static_cast<float>(fontsize), spacing);

    Vector2 textpos = {
        static_cast<float>(posX) - textSize.x / 2.0f,
        static_cast<float>(posY) - textSize.y / 2.0f
    };

    DrawTextEx(activeFont, text, textpos, static_cast<float>(fontsize), spacing, BLACK);
}

void Circle::Reset() {
    Moving = false;
}

bool Circle::Clicked() {
    return CheckCollisionPointCircle(
               GetMousePosition(),
               Vector2{static_cast<float>(posX), static_cast<float>(posY)},
               static_cast<float>(radius)) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
           !Moving &&
           clickable;
}
