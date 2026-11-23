#ifndef TEXT
#define TEXT
#include "raylib.h"

class Text {

public:
    Text() = default;
    Text(char *text, int posX, int posY, int w, int h, int fontSize, Color color, Font font, bool clickable);

    int GetPosX() const { return posX; }
    int GetPosY() const { return posY; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    void Render(); // render the text box
    bool Clicked(); // detects a single click in the text box
    void MoveX(int start, int moveX, int speed); // move the text box starting at a given frame, moving a given amount of units, at a given speed
    void MoveY(int start, int moveY, int speed); // same as above but for vertical movement
    void Reset(); // resets the text box to its initial positioning and resets its clock

private:
    int posX = 0, posY = 0; // current position of the text box
    int initX = 0, initY = 0; // initial position of the text box to be reset to when Reset() is called
    int width = 0, height = 0; // dimensions of text box
    int fontSize = 12;
    Font font{};
    Color color{}; // color of the text
    char* text = nullptr; // the displayed text
    Rectangle buttonShape{}; // rectangle object that determines the shape of the text box
    Color boxColor = {137, 207, 240, 255}; // color of the text box
    int clock = 0; // internal clock used to coordinate movement
    bool clickable = false; // boolean that determines if a text box is clickable
    bool currMoving = false; // boolean that determines if a text box is currently moving, moving boxes are not clickable
};

#endif
