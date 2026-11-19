#include <iostream>
#include "raylib.h"
#include "Button.h"
using namespace std;


int main() {

    int currPage = 0;
   
    InitWindow(800, 700, "Generative AI Infographic");
    SetTargetFPS(30);

    Button button1 = Button(50, 100, 240, 90, "Biometrics ");
    Button button2 = Button(725, 30, 50, 50, "BACK");
    Button button3 =Button (725,50,50,"Unmask);
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
Color babyBlue = { 137, 207, 240, 255 };
DrawText(" Pattern Recognition & Identifying through Biometrics ", 50, 40, 22, BLACK);
//Drawing A rectangle that have the first step of recognition 
DrawRectangleRounded((Rectangle){60, 150, 320, 90}, 0.2f, 4, babyBlue);
DrawText("Camera feed/Scrapped Image ", 75, 185, 14, BLACK);
DrawLine(380, 195, 440, 195, BLACK);
DrawRectangleRounded((Rectangle){440, 150, 310, 90}, 0.2f, 4, LIGHTGRAY);
//info from https://alexchohlaswood.com/assets/papers/patternizr.pdf
DrawText("raw digital media is captured from live surveillance", 455, 175, 12, BLACK);
DrawText(" feeds or scraped from digital resources",475,195,12,BLACK);

DrawLine(220, 240, 220, 260, BLACK);     
//second step in biometrics and AI recognition 
DrawRectangleRounded((Rectangle){60, 260, 320, 90}, 0.2f, 4, PINK);
DrawText("Facial Mapping ", 150, 295, 14, BLACK);
DrawLine(380,305,435,305,BLACK);
DrawRectangleRounded((Rectangle){450,270,280,90},0.2f,4,YELLOW);
DrawText("The Compute Vision phase",450,290,12,BLACK);
DrawText("detect distinct facial geometry",470,310,12,BLACK);


DrawRectangleRounded((Rectangle){60, 370, 320, 90}, 0.2f, 4, BLUE);

DrawLine(220,350,220,370,BLACK);
//Third step 
DrawText("Biometric face Encoding",75, 405, 13,BLACK);
DrawLine(380, 415, 440, 415, BLACK);
DrawRectangleRounded((Rectangle){440, 370, 310, 90}, 0.2f, 4, PURPLE);
DrawText("Translates the facial map into a high-", 455, 395, 12, BLACK);
 DrawText("dimensional vector for models to process.", 455, 415, 12, BLACK);
DrawLine(220, 460, 220, 480, BLACK);
//4th step
DrawRectangleRounded((Rectangle){60, 480, 320, 90}, 0.2f, 4, ORANGE);
DrawText("Random Similarity Matching",70,515,14,BLACK);
DrawLine(380,520,430,520,BLACK);
DrawRectangleRounded((Rectangle){440, 480, 330, 90}, 0.2f, 4, GRAY);

DrawText("Random similarity matching uses probabilistic models",460,500,12,BLACK );
DrawText(" like Patternizr classifiers to compare faceprints and identify matches.",460,520,12,BLACK);

button3.Render();
            if(button3.Clicked()){
                currPage = 2;
            }
            else if( currPage == 2){

           Texture2D photo= LoadTexture("passport-photo-portrait-middle-aged-man-looking-camera-white-studio-background-isolated_922936-66036.avif");
                
                double photoX=120.0f;
                double photoY=180.0f;
                double photoW=220.0f;
                double photoH=220.0f;

                Rectangle src {0.0f,0.0f,(float) photo.width,float(phto.height)};
                Rectangle dest = { (float)photoX, (float)photoY, (float)photoW, (float)photoH };
DrawTexturePro(photo, src, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
                double cx=photoX + photoW *0.50f;
                double cy=photoY+ photoH *0.40f;
                
                DrawCircle((int)cx, (int)cy, photoW*0.22f,Fade(RED,0.3f));
                
                 if (photo.id == 0) {
        CloseWindow();
        return -1;
                     
    }
            button2.Render();
            if (button2.Clicked()) {
                currPage = 0;
            }
        

        
        
        
        EndDrawing();

    }
UnloadTexture(photo);
    closeWindow();

return 0;

}
