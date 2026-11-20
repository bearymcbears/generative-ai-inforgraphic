#ifndef BUTTON
#define BUTTON
#include "raylib.h"
#include <string>

using namespace std;

class Button {

public:
    Button(int x, int y, int w, int h, string txt);
    void Render();
    bool Clicked();
    

private:
    int posX;
    int posY;
    int width;
    int height;
    string text;
    Rectangle buttonShape;
    Color color = {137, 207, 240, 255};
};


#endif