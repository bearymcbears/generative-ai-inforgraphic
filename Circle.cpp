# include "Circle.h"
# include <iostream>
using namespace std;
Circle::Circle(const char *text, int x, int y, int r, int fontsize, Color color, Font font) {
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
    Vector2 textpos={
        float(posX - MeasureText(this->text, fontsize) / 2.0f),
        float(posY - (float)radius-float(fontsize)-4.0f )
    };
    DrawTextEx(font, this->text, textpos, fontsize, 1.0f, BLACK);
}
