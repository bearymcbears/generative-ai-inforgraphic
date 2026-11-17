#ifndef BUTTON
#define BUTTON
#include "raylib.h"



class Button {

public:
    Button(int x, int y, int w, int h, char* txt);
    void Render();
    bool Clicked();
    

private:
    int posX;
    int posY;
    int width;
    int height;
    char* text;
    Rectangle buttonShape;
    Color color = {137, 207, 240, 255};
};


#endif