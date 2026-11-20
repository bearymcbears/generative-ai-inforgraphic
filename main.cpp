#include "raylib.h"
#include "Text.h"
#include "Connector.h"
using namespace std;

enum class Pages { Main, CollectionOfData, StorageOfData, Biometrics, Unmask };

int main()
{
    Pages currPage = Pages::Main;
    InitWindow(1200, 800, "Generative AI Infographic");

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);

    SetTargetFPS(30);

    Texture2D photo = LoadTexture("assets/images/_116381967_facemask.jpg");
    Texture2D facialtex = LoadTexture("assets/images/Gemini_Generated_Image_gsgu2gsgu2gsgu2g.jpg");
    bool hasPhoto = (photo.id != 0);

    Font defaultFont = GetFontDefault();
    Font interFont = LoadFont("assets/fonts/Inter-VariableFont_opsz,wght.ttf");

    Text bioButton("Biometrics", 50, 100, 240, 90, 16, BLACK, defaultFont, true);
    Text goToMainButton("BACK", 725, 30, 50, 50, 16, BLACK, defaultFont, true);
    Text unmaskButton("Unmask", 725, 90, 50, 50, 16, BLACK, defaultFont, true);
    Text goToBioButton("BACK", 725, 30, 50, 50, 16, BLACK, defaultFont, true);
    Text collectDataButton("Collection of Data", 300, 100, 240, 90, 16, BLACK, defaultFont, true);
    Text storageButton("Storage of Data", 550, 100, 240, 90, 16, BLACK, defaultFont, true);

    while (!WindowShouldClose()){
        BeginDrawing();

        if (currPage == Pages::Main){
            ClearBackground(WHITE);
            Text("AI AND SURVEILLANCE", 50, 40, 0, 0, 28, BLACK, interFont, false).Render();

            bioButton.Render();
            collectDataButton.Render();
            storageButton.Render();

            if (bioButton.Clicked())
            {
                currPage = Pages::Biometrics;
            } else if (collectDataButton.Clicked())
            {
                currPage = Pages::CollectionOfData;
            } else if (storageButton.Clicked())
            {
                currPage = Pages::StorageOfData;
            }
        }
        else if (currPage == Pages::Biometrics){
            ClearBackground(WHITE);
            Color babyBlue = {137, 207, 240, 255};
            Text(" Pattern Recognition & Identifying through Biometrics ", 50, 40, 0, 0, 22, BLACK, defaultFont, false).Render();

            DrawRectangleRounded((Rectangle){60, 150, 320, 90}, 0.2f, 4, babyBlue);
            Text("Camera feed/Scrapped Image ", 75, 185, 0, 0, 14, BLACK, defaultFont, false).Render();
            DrawLine(380, 195, 440, 195, BLACK);
            DrawRectangleRounded((Rectangle){440, 150, 310, 90}, 0.2f, 4, LIGHTGRAY);
            Text("raw digital media is captured from live surveillance", 455, 175, 0, 0, 12, BLACK, defaultFont, false).Render();
            Text(" feeds or scraped from digital resources", 475, 195, 0, 0, 12, BLACK, defaultFont, false).Render();

            DrawLine(220, 240, 220, 260, BLACK);

            DrawRectangleRounded((Rectangle){60, 260, 320, 90}, 0.2f, 4, PINK);
            Text("Facial Mapping ", 150, 295, 0, 0, 14, BLACK, defaultFont, false).Render();
            if (facialtex.id != 0)
            {
                DrawTextureEx(facialtex, (Vector2){265.0f, 280.0f}, 0.08f, 0.08f, WHITE);
            }
            DrawLine(380, 305, 435, 305, BLACK);
            DrawRectangleRounded((Rectangle){450, 270, 280, 90}, 0.2f, 4, YELLOW);
            Text("The Compute Vision phase", 450, 290, 0, 0, 12, BLACK, defaultFont, false).Render();
            Text("detect distinct facial geometry", 470, 310, 0, 0, 12, BLACK, defaultFont, false).Render();

            DrawLine(220, 350, 220, 370, BLACK);

            DrawRectangleRounded((Rectangle){60, 370, 320, 90}, 0.2f, 4, BLUE);
            Text("Biometric face Encoding", 75, 405, 0, 0, 13, BLACK, defaultFont, false).Render();
            DrawLine(380, 415, 440, 415, BLACK);
            DrawRectangleRounded((Rectangle){440, 370, 310, 90}, 0.2f, 4, PURPLE);
            Text("Translates the facial map into a high-", 455, 395, 0, 0, 12, BLACK, defaultFont, false).Render();
            Text("dimensional vector for models to process.", 455, 415, 0, 0, 12, BLACK, defaultFont, false).Render();

            DrawLine(220, 460, 220, 480, BLACK);

            DrawRectangleRounded((Rectangle){60, 480, 320, 90}, 0.2f, 4, ORANGE);
            Text("Random Similarity Matching", 70, 515, 0, 0, 14, BLACK, defaultFont, false).Render();
            DrawLine(380, 520, 430, 520, BLACK);
            DrawRectangleRounded((Rectangle){440, 480, 330, 90}, 0.2f, 4, GRAY);
            Text("Random similarity matching uses probabilistic models", 460, 500, 0, 0, 12, BLACK, defaultFont, false).Render();
            Text(" like Patternizr classifiers to compare faceprints", 460, 520, 0, 0, 12, BLACK, defaultFont, false).Render();
            Text("and identify matches.", 460, 540, 0, 0, 12, BLACK, defaultFont, false).Render();

            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }

            unmaskButton.Render();
            if (unmaskButton.Clicked())
            {
                currPage = Pages::Unmask;
            }
        }
        else if (currPage == Pages::Unmask){
            ClearBackground(RAYWHITE);
            DrawTexture(photo, screenWidth / 2 - photo.width / 2, screenHeight / 2 - photo.height / 2, WHITE);

            goToBioButton.Render();
            if (goToBioButton.Clicked())
            {
                currPage = Pages::Biometrics;
            }
        }
        else if (currPage == Pages::CollectionOfData){
            ClearBackground(WHITE);

            const int fs = 14;

            Text sensor("Sensor records automatically:\ncamera, plate reader, microphone, phone GPS", 200, 10, 340, 50, fs, BLACK, interFont, false);
            Text software("Software turns the raw recording into data", 40, 94, 660, 34, fs, BLACK, interFont, false);

            Text plate("Plate photo: find the\nplate, then read its\ncharacters as text", 40, 162, 200, 56, fs, BLACK, interFont, false);
            Text sound("Sound: locate it by comparing\nwhen each mic heard it, then\nclassify as gunshot or not", 255, 162, 230, 56, fs, BLACK, interFont, false);
            Text video("Video: find faces,\ncars, or movement", 500, 162, 200, 56, fs, BLACK, interFont, false);

            Text tag("Tag it with time, place, and camera ID", 40, 252, 660, 34, fs, BLACK, interFont, false);
            Text check("Check against a watch\nlist or gunshot model", 270, 340, 200, 40, fs, BLACK, interFont, false);

            Text alert("Alert, often reviewed\nby a person first", 40, 340, 160, 40, fs, BLACK, interFont, false);
            Text saved("Saved anyway, for\ndays or longer", 540, 340, 160, 40, fs, BLACK, interFont, false);
            Text officer("Officer is notified\nand responds", 40, 414, 160, 40, fs, BLACK, interFont, false);
            Text shared("Shared databases and dashboards like the NYPD Domain Awareness System", 40, 500, 660, 40, fs, BLACK, interFont, false);

            Connector(sensor, software, Side::Bottom, Side::Top).DrawConnector();
            Connector(tag, check, Side::Bottom, Side::Top).DrawConnector();
            Connector(check, alert, Side::Left, Side::Right).DrawConnector();
            Connector(check, saved, Side::Right, Side::Left).DrawConnector();
            Connector(alert, officer, Side::Bottom, Side::Top).DrawConnector();

            DrawLineEx({140, 128}, {140, 162}, 3.0f, BLACK);   // software -> plate
            DrawLineEx({370, 128}, {370, 162}, 3.0f, BLACK);   // software -> sound
            DrawLineEx({600, 128}, {600, 162}, 3.0f, BLACK);   // software -> video
            DrawLineEx({140, 218}, {140, 252}, 3.0f, BLACK);   // plate -> tag
            DrawLineEx({370, 218}, {370, 252}, 3.0f, BLACK);   // sound -> tag
            DrawLineEx({600, 218}, {600, 252}, 3.0f, BLACK);   // video -> tag
            DrawLineEx({120, 454}, {120, 500}, 3.0f, BLACK);   // officer -> shared
            DrawLineEx({620, 380}, {620, 500}, 3.0f, BLACK);   // saved -> shared

            sensor.Render(); software.Render();
            plate.Render(); sound.Render(); video.Render();
            tag.Render(); check.Render();
            alert.Render(); saved.Render(); officer.Render(); shared.Render();

            // Labels on the decision lines
            Text("match", 219, 342, 0, 0, 12, DARKGRAY, interFont, false).Render();
            Text("no match", 480, 342, 0, 0, 12, DARKGRAY, interFont, false).Render();

            goToMainButton.Render();
            if (goToMainButton.Clicked()){
                currPage = Pages::Main;
            }
        }
        else if (currPage == Pages::StorageOfData){
            ClearBackground(WHITE);

            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }
        }

        EndDrawing();
    }

    UnloadFont(interFont);
    UnloadTexture(photo);
    UnloadTexture(facialtex);
    CloseWindow();
    return 0;
}