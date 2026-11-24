#include "Circle.h"
// A circle class that takes a text, posX, posY, Radius, fontSize, Color, and can be clikced to work as a button 

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
// Draws the circle and centers the label text inside it (using the default font if none is set).void Circle::Render() {
    DrawCircle(posX, posY, radius, color);

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
// Reset movement state so thar the circle can be clicked again 
void Circle::Reset() {
    Moving = false;
}
// Return True when the circle is clicked (work as button)
bool Circle::Clicked() {
    return CheckCollisionPointCircle(
               GetMousePosition(),
               Vector2{static_cast<float>(posX), static_cast<float>(posY)},
               static_cast<float>(radius)) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
           !Moving &&
           clickable;
}
