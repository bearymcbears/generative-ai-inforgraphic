#include <iostream>
#include "raylib.h"
#include "Button.h"
using namespace std;


int main() {

    int currPage = 0;
   
    InitWindow(800, 700, "Generative AI Infographic");
    SetTargetFPS(30);

    Button button1 = Button(50, 100, 240, 90, "Collection of Data");
    Button button2 = Button(725, 30, 50, 50, "BACK");

    while (!WindowShouldClose()) {

        BeginDrawing();

        if (currPage == 0) {

            ClearBackground(Color{248, 246, 240, 255});
            DrawText("AI AND SURVEILLANCE", 50, 40, 28, BLACK);

            button1.Render();
            if (button1.Clicked()) {
                currPage = 1;
            }

        }
        else if (currPage == 1) {

            ClearBackground(Color{251, 238, 172, 255});
            DrawText("Collection of Data", 50, 40, 28, BLACK);

            button2.Render();
            if (button2.Clicked()) {
                currPage = 0;
            }

        }
        
        
        EndDrawing();

    }


return 0;

}