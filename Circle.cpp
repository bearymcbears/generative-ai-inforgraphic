# include "Circle.h"
# include <iostream>
using namespace std;
Circle::Circle(const char *text, int x, int y, int r, int fontsize, Color color, Font font, bool clickable=0) : posX(x), posY(y), radius(r), fontsize(fontsize), color(color), font(font), clickable(clickable) {
    this->text = text;
    posX = x;
    posY = y;
    radius = r;
    this->fontsize = fontsize;
    this->color = color;
    this->font = font;
}
void Circle::Render() {
    DrawCircle(posX, posY, radius, color);

    float spacing = 1.0f;
    Vector2 textSize = MeasureTextEx(font, this->text, static_cast<float>(fontsize), spacing);

    Vector2 textpos = {
        static_cast<float>(posX) - textSize.x / 2.0f,
        static_cast<float>(posY) - textSize.y / 2.0f
    };

    DrawTextEx(font, this->text, textpos, static_cast<float>(fontsize), spacing, BLACK);
}

bool Circle::Clicked() {
    return CheckCollisionPointCircle(GetMousePosition(), Vector2{static_cast<float>(posX), static_cast<float>(posY)}, static_cast<float>(radius)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !Moving && clickable;
}
