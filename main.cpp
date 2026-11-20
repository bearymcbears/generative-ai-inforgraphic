#include <iostream>
#include "raylib.h"
#include "Button.h"
using namespace std;

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 700;
    int currPage = 0;

    InitWindow(screenWidth, screenHeight, "Generative AI Infographic");
    SetTargetFPS(30);
    Texture2D photo = LoadTexture("_116381967_facemask.jpg");
    Texture2D facialtex = LoadTexture("Gemini_Generated_Image_gsgu2gsgu2gsgu2g.jpg"); // used https://www.raylib.com/examples/textures/loader.html?name=textures_image_drawing to upload pictures
    bool hasPhoto = (photo.id != 0);
    

    Button button1 = Button(50, 100, 240, 90, "Biometrics ", 1);
    Button button2 = Button(725, 30, 50, 50, "BACK", 1);
    Button button3 = Button(725, 90, 50, 50, "Unmask", 1);
    Button button4 = Button(725, 150, 50, 50, "BACK", 1);
    Button button5 = Button(150, 100, 240, 90, "Collection of Data", 1);
    Button button6 = Button(250, 100, 240, 90, "Storage of Data", 1);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        if (currPage == 0)
        {

            ClearBackground(Color{248, 246, 240, 255});
            DrawText("AI AND SURVEILLANCE", 50, 40, 28, BLACK);

            button1.Render();
            if (button1.Clicked())
            {
                currPage = 1;
            }
        }
        else if (currPage == 1)
        {
            ClearBackground(Color{251, 238, 172, 255});
            // DrawText("Collection of Data", 50, 40, 28, BLACK);
            Color babyBlue = {137, 207, 240, 255};
            DrawText(" Pattern Recognition & Identifying through Biometrics ", 50, 40, 22, BLACK);
            // Drawing A rectangle that have the first step of recognition
            DrawRectangleRounded((Rectangle){60, 150, 320, 90}, 0.2f, 4, babyBlue);
            DrawText("Camera feed/Scrapped Image ", 75, 185, 14, BLACK);
            DrawLine(380, 195, 440, 195, BLACK);
            DrawRectangleRounded((Rectangle){440, 150, 310, 90}, 0.2f, 4, LIGHTGRAY);
            // info from https://alexchohlaswood.com/assets/papers/patternizr.pdf
            DrawText("raw digital media is captured from live surveillance", 455, 175, 12, BLACK);
            DrawText(" feeds or scraped from digital resources", 475, 195, 12, BLACK);

            DrawLine(220, 240, 220, 260, BLACK);
            // second step in biometrics and AI recognition
            DrawRectangleRounded((Rectangle){60, 260, 320, 90}, 0.2f, 4, PINK);
            
            DrawText("Facial Mapping ", 150, 295, 14, BLACK);
           
           
            if(facialtex.id!=0){
            DrawTextureEx(facialtex,(Vector2){265.0f,280.0f},0.08f,0.08f,WHITE);
            }
            DrawLine(380, 305, 435, 305, BLACK);
            DrawRectangleRounded((Rectangle){450, 270, 280, 90}, 0.2f, 4, YELLOW);
            DrawText("The Compute Vision phase", 450, 290, 12, BLACK);
            DrawText("detect distinct facial geometry", 470, 310, 12, BLACK);

            DrawRectangleRounded((Rectangle){60, 370, 320, 90}, 0.2f, 4, BLUE);

            DrawLine(220, 350, 220, 370, BLACK);
            // Third step
            DrawText("Biometric face Encoding", 75, 405, 13, BLACK);
            DrawLine(380, 415, 440, 415, BLACK);
            DrawRectangleRounded((Rectangle){440, 370, 310, 90}, 0.2f, 4, PURPLE);
            DrawText("Translates the facial map into a high-", 455, 395, 12, BLACK);
            DrawText("dimensional vector for models to process.", 455, 415, 12, BLACK);
            DrawLine(220, 460, 220, 480, BLACK);
            // 4th step
            DrawRectangleRounded((Rectangle){60, 480, 320, 90}, 0.2f, 4, ORANGE);
            DrawText("Random Similarity Matching", 70, 515, 14, BLACK);
            DrawLine(380, 520, 430, 520, BLACK);
            DrawRectangleRounded((Rectangle){440, 480, 330, 90}, 0.2f, 4, GRAY);

            DrawText("Random similarity matching uses probabilistic models", 460, 500, 12, BLACK);
            DrawText(" like Patternizr classifiers to compare faceprints", 460, 520, 12, BLACK);
            DrawText("and identify matches.", 460, 540, 12, BLACK);

            button2.Render();
            if (button2.Clicked())
            {
                currPage = 0;
            }
            button3.Render();
            if (button3.Clicked())
            {
                currPage = 2;
            }
        }
        else if (currPage == 2)
        {
            ClearBackground(RAYWHITE);
            DrawTexture(photo, screenWidth / 2 - photo.width / 2, screenHeight / 2 - photo.height / 2, WHITE); /* used https://www.raylib.com/examples/textures/loader.html?name=textures_image_drawing
                                                                                                                  to upload the Image*/

            button4.Render();
            if (button4.Clicked())
            {
                currPage = 1;
            }
        } else if (currPage == 3) {

        } else if (currPage == 4) {

        }

        EndDrawing();
    }
    UnloadTexture(photo);
      UnloadTexture(facialtex);
    CloseWindow();
    return 0;
}
