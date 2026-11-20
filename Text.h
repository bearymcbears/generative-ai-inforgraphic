#ifndef TEXT
#define TEXT
#include "raylib.h"

class Text {

public:
    Text(char *text, int posX, int posY, int w, int h, int fontSize, Color color, Font font, bool clickable);
    void Render(); // render the text box
    bool Clicked(); // detects a single click in the text box
    void MoveX(int start, int moveX, int speed); // move the text box starting at a given frame, moving a given amount of units, at a given speed
    void MoveY(int start, int moveY, int speed); // same as above but for vertical movement
    void Reset(); // resets the text box to its initial positioning and resets its clock

private:
    int posX, posY; // current position of the text box
    int initX, initY; // initial position of the text box to be reset to when Reset() is called
    int width, height; // dimensions of text box
    int fontSize;
    Color color;
    Font font;
    char* text; // the displayed text
    Rectangle buttonShape; // rectangle object that determines the shape of the text box
    Color color = {137, 207, 240, 255}; // color of the text box
    int clock = 0; // internal clock used to coordinate movement
    bool clickable; // boolean that determines if a text box is clickable
    bool currMoving = false; // boolean that determines if a text box is currently moving, moving boxes are not clickable
};


#endif