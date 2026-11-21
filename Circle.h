#include "raylib.h"
#include <string>

class Circle{
public:
 Circle(const char *text, int x, int y, int r, int fontsize, Color color, Font font);
 int GetposX(){
    return posX;
 }
int GetposY(){
    return posY;

}
int GetRadius(){
 return  radius;
}


void Render();

private:
int posX=0;
int posY=0;
int radius=0;
int fontsize=12;
Color color;
Font font;
const char *text;
};
