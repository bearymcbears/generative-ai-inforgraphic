#ifndef CIRCLE_H
#define CIRCLE_H

#include "raylib.h"
#include <string>
// Interactive circle UI element that displays centered text and can act as a clickable button.
class Circle {
public:
    Circle() = default;
    Circle(const char *text, int x, int y, int r, int fontsize, Color color, Font font, bool clickable);

    int GetposX() const { return posX; }
    int GetposY() const { return posY; }
    int GetRadius() const { return radius; }

    void Render();
    void Reset();
    bool Clicked();

private:
    int posX = 0;
    int posY = 0;
    int radius = 0;
    int fontsize = 12;
    Color color{};
    Font font{};
    const char *text = nullptr;
    bool clickable = false;
    bool Moving = false;
};

#endif
