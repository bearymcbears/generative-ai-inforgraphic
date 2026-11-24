#include "raylib.h"
#include "Text.h"
#include "Connector.h"
#include "Circle.h"
#include <iostream>
#include <cmath>
#include "PlateRecognizer.h"
/*CS 103 Hacakathon #2
  Creating an Interactive Infographic with Raylib to show the impact of
   generative AI on surveillance technology on society
    Team 18 */

using namespace std;

// enum learned from https://www.w3schools.com/cpp/cpp_enum.asp
enum class Pages
{
    Main,
    CollectionOfData,
    StorageOfData,
    Biometrics,
    Unmask,
    StorageOfDataExplained,
    Predictions,
    VisualizePredictions,
    Dashboard,
    DASHBOARDVISUALIZE,
    MISSION,
    InteractiveGame,
    PlateReader
};

int main()
{
    // used to store the position of the ball in the interactive game
    //  Used https://www.raylib.com/examples.html  raylib examples to learn how to use the library and implement the interactive game
    // used https://www.stopspying.org/guilt-by-association to made my reasearch about  discrimination and policing bias
    // used also to inform me more on Survillence in East harlem and public housing https://citylimits.org/cameras-or-community-what-keeps-harlem-safe/
    Vector2 ballPosition = {-100.0f, -100.0f};
    Color ballColor = DARKBLUE;
    Sound alertSound = LoadSound("assets/fonts/freesound_community-beep-warning-6387.mp3");
    PlateRecognizer::Init();

    bool imageUploaded = false;
    string imagePath = "";
    string resultMessage = "Plate Result: ";
    Texture2D uploadedImage = {0};

    const int screenWidth = 1200;
    const int screenHeight = 800;
    int spacing = 130;
    int centerx = 600 + 50;
    int centery = (800 / 2) - 90;
    Pages currPage = Pages::Main;

    InitWindow(1200, 800, "Generative AI Infographic");
    int midX = centerx - 250;
    int midY = (centery + spacing / 2) - 25;
    int midW = 500;
    int midH = 90;

    SetTargetFPS(30);
    // Load textures for the images used in the infographic
    Texture2D photo = LoadTexture("assets/images/_116381967_facemask.jpg");
    Texture2D facialtex = LoadTexture("assets/images/Gemini_Generated_Image_3iwtae3iwtae3iwt.jpg");
    Texture2D camerascrapped = LoadTexture("assets/images/Gemini_Generated_Image_2laahr2laahr2laa.jpg");
    Texture2D plateImage = LoadTexture("assets/images/test car image.png");
    Texture2D predictionstex = LoadTexture("assets/images/policepredictions.jpg.jpg");
    Texture2D DAS = LoadTexture("assets/images/DAS_visualization.jpg");

    bool hasPhoto = (photo.id != 0);
    // Load fonts for the text used in the infographic
    Font defaultFont = GetFontDefault();
    Font interFont = LoadFont("assets/fonts/Inter-VariableFont_opsz,wght.ttf");
    Font MyFont = LoadFont("assets/fonts/Lato-Regular.ttf");
    // Create the buttons and text boxes used in the infographic
    Circle BioButton("Biometrics", 100, 300, 70, 16, YELLOW, MyFont, true);
    Circle CollectionButton("Collection of Data", 300, 300, 70, 16, GREEN, MyFont, true);
    Circle StorageButton("Storage of Data", 500, 300, 70, 16, BLUE, MyFont, true);
    Circle PredictionsButton("Predictions", 700, 300, 70, 16, RED, MyFont, true);
    Circle Dashboard("Managing\n Dashboard ", 900, 300, 70, 16, GRAY, MyFont, true);
    // create the text boxes used in the infographic
    Text Mission("Mission", 1000, 30, 80, 45, 16, BLACK, MyFont, true);
    Text Game("interactive Game ", 1000, 100, 160, 80, 12, BLACK, MyFont, true);
    Text VisualizePredictionsButton("Visualize", 1050, 30, 80, 45, 16, BLACK, MyFont, true);
    Text goToMainButton("BACK", 925, 30, 80, 45, 16, BLACK, MyFont, true);
    Text unmaskButton("Unmask", 925, 90, 80, 45, 16, BLACK, MyFont, true);
    Text goToBioButton("BACK", 925, 30, 80, 45, 16, BLACK, MyFont, true);
    Text goToCollectionButton("BACK", 925, 30, 80, 45, 16, BLACK, MyFont, true);
    Text Explaination("EXPLAIN", 925, 90, 80, 45, 16, BLACK, MyFont, true);
    Text NameButton("Name: joseph rivera\nAge: 27\nSkin Tone: Medium\nOrigin: New York", 50, 100, 250, 250, 20, BLACK, defaultFont, false);
    Text Back("BACK", 925, 30, 80, 45, 16, BLACK, MyFont, true);
    // create circles used to visualize the storage of data in the infographic
    Circle circle1("DATA", centerx - spacing / 2, (centery - spacing / 2) - 90, 30, 20, YELLOW, MyFont, false);
    Circle circle2("DATA", centerx + spacing / 2, (centery - spacing / 2) - 90, 30, 20, GREEN, MyFont, false);
    Circle circle3("DATA", centerx - spacing / 2, (centery + spacing / 2) - 90, 30, 20, BLUE, MyFont, false);
    Circle circle4("DATA", centerx + spacing / 2, (centery + spacing / 2) - 90, 30, 20, RED, MyFont, false);

    Text MIDDLEREC("Adjustable Blocks of Data", midX, midY, midW, midH, 16, BLACK, MyFont, false);
    int boxW = 150;
    int boxH = 70;
    int boxY = midY + midH + 35;
    // create text boxes to explain the storage of data in the infographic
    Text leftBox("Live Storage", midX, boxY, boxW, boxH, 14, BLACK, MyFont, false);
    Text middleBox("Encrypted Archive", midX + (midW / 2) - (boxW / 2), boxY, boxW, boxH, 14, BLACK, MyFont, false);
    Text rightBox("Auto-Purge", midX + midW - boxW, boxY, boxW, boxH, 14, BLACK, MyFont, false);

    InitAudioDevice();

    Texture2D manhattanMap = LoadTexture("assets/images/manhattanmap.jpg");

    // used https://www.raylib.com/examples.html  raylib examples to learn how to use the library and implement the interactive game
    /* used Gemini To create the positions of the spots on the Map when prompt
     How Can I create positions for the spots on the map
    Accessed November 2026*/
    struct ManhattanSpot
    {
        const char *name;
        float u;
        float v;
        bool isFlaggedArea;
        bool spotted;
        const char *infoText;
    };

    ManhattanSpot manhattanSpots[] = {
        {"", 0.37f, 0.08f, true, false, "A major Black Neighborhood Flagged RED: Concentrated patrols/data can fuel bias & unfair racial labeling"},
        {"", 0.60f, 0.15f, true, false, " A major Black Neighborhood Flagged RED: High enforcement focus can reinforce a feedback loop"},
        {".", 0.32f, 0.17f, true, false, "A major Black Neighborhood  Flagged RED: Adjacent to Harlem; repeated alerts reinforce stereotyping"},
        {"", 0.32f, 0.31f, false, false, "Safe / BLUE: Lower targeted flag in this simulation"},
        {"", 0.64f, 0.38f, false, false, "Safe / BLUE: Lower targeted flag in this simulation"},
        {"", 0.50f, 0.50f, false, false, "Safe / BLUE: Lower targeted flag in this simulation"},
        {"", 0.38f, 0.72f, false, false, "Safe / BLUE: Lower targeted flag in this simulation"},
        {"", 0.52f, 0.93f, false, false, "Safe / BLUE: Lower targeted flag in this simulation"},
        {
            "",
        }};
    const int manhattanSpotCount = sizeof(manhattanSpots) / sizeof(manhattanSpots[0]);

    const char *statusBanner = "Move cursor over Manhattan neighborhoods to spot areas (RED = flagged, BLUE = safe)";
    Color statusColor = SKYBLUE;

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        if (currPage == Pages::Main)
        {

            ClearBackground(WHITE);
            Text("AI AND SURVEILLANCE", 50, 40, 0, 0, 28, BLACK, MyFont, false).Render();
            Text("Click Mission to learn about the mission of this infographic\n Click the Game button to play the interactive game", 50, 150, 0, 0, 14, BLACK, MyFont, false).Render();
            Text("Then, Click the Circle buttons to learn about each stage of the surveillance pipeline", 50, 200, 0, 0, 14, BLACK, MyFont, false).Render();
            Mission.Render();

            BioButton.Render();
            CollectionButton.Render();
            StorageButton.Render();
            PredictionsButton.Render();
            Dashboard.Render();
            Game.Render();
            Connector(BioButton, CollectionButton, Side::Right, Side::Left).DrawConnector();
            Connector(CollectionButton, StorageButton, Side::Right, Side::Left).DrawConnector();
            Connector(StorageButton, PredictionsButton, Side::Right, Side::Left).DrawConnector();
            Connector(PredictionsButton, Dashboard, Side::Right, Side::Left).DrawConnector();

            if (Mission.Clicked())
            {
                currPage = Pages::MISSION;
            }
            else if (BioButton.Clicked())
            {
                currPage = Pages::Biometrics;
            }
            else if (CollectionButton.Clicked())
            {
                currPage = Pages::CollectionOfData;
            }
            else if (StorageButton.Clicked())
            {
                currPage = Pages::StorageOfData;
            }
            else if (PredictionsButton.Clicked())
            {
                currPage = Pages::Predictions;
            }
            else if (Game.Clicked())
            {
                currPage = Pages::InteractiveGame;
            }
        }
        else if (currPage == Pages::MISSION)
        {
            ClearBackground(WHITE);
            Text("Mission", 50, 40, 0, 0, 28, BLACK, MyFont, false).Render();
            Text missionText(
                "Mission: This interactive infographic aims to demystify how modern surveillance and predictive\n"
                "policing operate from start to finish - tracing the journey from biometric identification\n"
                "and wide-scale data collection to long-term data storage, algorithmic predictions,\n"
                "and operator dashboards. By examining how generative AI and predictive models reshape\n"
                "each stage of this pipeline, it equips the public to understand how raw signals and\n"
                "synthetic or reconstructed outputs are turned into actionable decisions, where privacy\n"
                "and civil liberties are put at risk, and how historical inequities and feedback loops\n"
                "can fuel bias and discrimination.\n\n"
                "Ultimately, the goal is to move beyond abstract headlines and give everyday people clear,\n"
                "grounded insight into these systems so communities can ask sharper questions, spot\n"
                "potential harms early, and advocate for meaningful transparency, human accountability,\n"
                "and strong civil-rights safeguards.",
                50, 150, 0, 0, 20, BLACK, MyFont, false);
            missionText.Render();

            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }
        }
        else if (currPage == Pages::Biometrics)
        {
            ClearBackground(WHITE);
            Text ClicK("(click unmask to view how Biometrics works) ", 50, 100, 0, 0, 14, BLACK, MyFont, false);
            ClicK.Render();
            Color babyBlue = {137, 207, 240, 255};
            Text(" Pattern Recognition & Identifying through Biometrics ", 50, 40, 0, 0, 22, BLACK, MyFont, false).Render();
            Text BOX1("Camera feed/Scrapped Image", 75, 185, 250, 60, 14, BLACK, MyFont, false);
            BOX1.Render();
            Text BOX2("raw digital media is captured from live surveillance feeds.", 455, 185, 350, 60, 12, BLACK, MyFont, false);
            BOX2.Render();
            Text BOX3("Facial Mapping", 75, 320, 250, 60, 14, BLACK, MyFont, false);
            BOX3.Render();
            Text BOX4("The Compute Vision phase detects distinct facial geometry.", 455, 320, 350, 60, 12, BLACK, MyFont, false);
            BOX4.Render();
            Text BOX5("Biometric face Encoding", 75, 450, 250, 60, 13, BLACK, MyFont, false);
            BOX5.Render();
            Text BOX6("Translates the facial map\n into a high-dimensional\n vector for models to process.", 455, 450, 350, 60, 12, BLACK, MyFont, false);
            BOX6.Render();
            Text BOX7("Random Similarity Matching", 75, 580, 250, 60, 14, BLACK, MyFont, false);
            BOX7.Render();
            Text BOX8("Random similarity matching uses probabilistic models\n like Patternizr classifiers to compare\n faceprints and identify matches.", 455, 580, 350, 60, 12, BLACK, MyFont, false);
            BOX8.Render();

            Connector(BOX1, BOX2, Side::Right, Side::Left).DrawConnector();
            Connector(BOX3, BOX4, Side::Right, Side::Left).DrawConnector();
            Connector(BOX5, BOX6, Side::Right, Side::Left).DrawConnector();
            Connector(BOX7, BOX8, Side::Right, Side::Left).DrawConnector();
            Connector(BOX1, BOX3, Side::Bottom, Side::Top).DrawConnector();
            Connector(BOX5, BOX7, Side::Bottom, Side::Top).DrawConnector();
            Connector(BOX3, BOX5, Side::Bottom, Side::Top).DrawConnector();

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
        else if (currPage == Pages::Unmask)
        {
            ClearBackground(RAYWHITE);
            Text("A visualization of how Biometrics Work ", 50, 40, 0, 0, 28, BLACK, MyFont, false).Render();

            if (photo.id != 0)
            {
                DrawTexture(photo, screenWidth / 2 - photo.width / 2, screenHeight / 2 - photo.height / 2, WHITE);
            }
            NameButton.Render();
            goToBioButton.Render();
            if (goToBioButton.Clicked())
            {
                currPage = Pages::Biometrics;
            }
        }

        else if (currPage == Pages::CollectionOfData)
        {
            ClearBackground(WHITE);

            const int fs = 14;

            Text sensor("Sensor records automatically:\ncamera, plate reader, microphone, phone GPS", 200, 10, 340, 50, fs, BLACK, interFont, false);
            Text software("Software turns the raw recording into data", 40, 94, 660, 34, fs, BLACK, MyFont, false);

            Text plate("Plate photo: find the\nplate, then read its\ncharacters as text", 40, 162, 200, 56, fs, BLACK, MyFont, false);
            Text sound("Sound: locate it by comparing\nwhen each mic heard it, then\nclassify as gunshot or not", 255, 162, 230, 56, fs, BLACK, interFont, false);
            Text video("Video: find faces,\ncars, or movement", 500, 162, 200, 56, fs, BLACK, interFont, false);

            Text tag("Tag it with time, place, and camera ID", 40, 252, 660, 34, fs, BLACK, interFont, false);
            Text check("Check against a watch\nlist or gunshot model", 270, 340, 200, 40, fs, BLACK, interFont, false);

            Text alert("Alert, often reviewed\nby a person first", 40, 340, 160, 40, fs, BLACK, interFont, false);
            Text saved("Saved anyway, for\ndays or longer", 540, 340, 160, 40, fs, BLACK, interFont, false);
            Text officer("Officer is notified\nand responds", 40, 414, 160, 40, fs, BLACK, interFont, false);
            Text shared("Shared databases and dashboards like the NYPD Domain Awareness System", 40, 500, 660, 40, fs, BLACK, interFont, false);

            Text readPlate("Read Plate Example", 925, 100, 50, 50, 16, BLACK, defaultFont, true);

            Connector(sensor, software, Side::Bottom, Side::Top).DrawConnector();
            Connector(tag, check, Side::Bottom, Side::Top).DrawConnector();
            Connector(check, alert, Side::Left, Side::Right).DrawConnector();
            Connector(check, saved, Side::Right, Side::Left).DrawConnector();
            Connector(alert, officer, Side::Bottom, Side::Top).DrawConnector();

            DrawLineEx({140, 128}, {140, 162}, 3.0f, BLACK);
            DrawLineEx({370, 128}, {370, 162}, 3.0f, BLACK);
            DrawLineEx({600, 128}, {600, 162}, 3.0f, BLACK);
            DrawLineEx({140, 218}, {140, 252}, 3.0f, BLACK);
            DrawLineEx({370, 218}, {370, 252}, 3.0f, BLACK);
            DrawLineEx({600, 218}, {600, 252}, 3.0f, BLACK);
            DrawLineEx({120, 454}, {120, 500}, 3.0f, BLACK);
            DrawLineEx({620, 380}, {620, 500}, 3.0f, BLACK);

            sensor.Render();
            software.Render();
            plate.Render();
            sound.Render();
            video.Render();
            tag.Render();
            check.Render();
            alert.Render();
            saved.Render();
            officer.Render();
            shared.Render();
            readPlate.Render();

            Text("match", 219, 342, 0, 0, 12, DARKGRAY, interFont, false).Render();
            Text("no match", 480, 342, 0, 0, 12, DARKGRAY, interFont, false).Render();

            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }
            if (readPlate.Clicked())
            {
                currPage = Pages::PlateReader;
            }
        }
        else if (currPage == Pages::PlateReader)
        {
            ClearBackground(WHITE);
            Text("Plate Reader", 50, 40, 0, 0, 28, BLACK, interFont, false).Render();

            int xPos = screenWidth / 2 - 500;
            int yPos = screenHeight / 2 - 200;
            Rectangle dropZone = {(float)xPos, (float)yPos, 400.0f, 400.0f};
            Text imageToAnalyze("Image to Analyze", xPos, yPos - 50, 400, 50, 20, BLACK, interFont, false, WHITE);
            Text uploadImageArea = Text("Drop Image Here", xPos, yPos, 400, 400, 20, WHITE, interFont, false, LIGHTGRAY);
            Text plateResult(resultMessage.c_str(), xPos + 500, yPos - 50, 400, 50, 20, BLACK, interFont, false, WHITE);

            if (IsFileDropped())
            {
                FilePathList dropped = LoadDroppedFiles();
                Vector2 mouse = GetMousePosition();

                if (CheckCollisionPointRec(mouse, dropZone) && dropped.count > 0)
                {
                    string path = dropped.paths[0];
                    if (CheckCollisionPointRec(mouse, dropZone) && dropped.count > 0)
                    {
                        string path = dropped.paths[0];
                        if (IsFileExtension(path.c_str(), ".png;.jpg;.jpeg"))
                        {
                            imagePath = path;
                            imageUploaded = true;

                            if (uploadedImage.id != 0)
                                UnloadTexture(uploadedImage);

                            Image img = LoadImage(imagePath.c_str());
                            ImageResize(&img, 400, 400);
                            uploadedImage = LoadTextureFromImage(img);
                            UnloadImage(img);

                            resultMessage = "Plate Result: " + PlateRecognizer::ReadPlate(imagePath.c_str());
                        }
                        else
                        {
                            resultMessage = "Invalid file type. Please drop a PNG or JPG image.";
                        }
                    }
                }

                UnloadDroppedFiles(dropped);
            }

            if (uploadedImage.id != 0)
            {
                DrawTexture(uploadedImage, xPos, yPos, WHITE);
            }
            else
            {
                uploadImageArea.Render();
            }
            goToCollectionButton.Render();
            imageToAnalyze.Render();
            plateResult.Render();

            // string text = PlateRecognizer::ReadPlate("assets/images/test car image.png");

            if (goToCollectionButton.Clicked())
            {
                currPage = Pages::CollectionOfData;
            }
        }
        else if (currPage == Pages::StorageOfData)
        {

            ClearBackground(WHITE);
            Text storage("A Visualization of how Data is stored\n click Explaination to learn more", 50, 40, 0, 0, 22, BLACK, MyFont, false);
            storage.Render();

            circle1.Render();
            circle2.Render();
            circle3.Render();
            circle4.Render();
            MIDDLEREC.Render();
            leftBox.Render();
            middleBox.Render();
            rightBox.Render();

            Connector(MIDDLEREC, leftBox, Side::Bottom, Side::Top).DrawConnector();
            Connector(MIDDLEREC, middleBox, Side::Bottom, Side::Top).DrawConnector();
            Connector(MIDDLEREC, rightBox, Side::Bottom, Side::Top).DrawConnector();

            goToMainButton.Render();
            Explaination.Render();

            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }
            else if (Explaination.Clicked())
            {
                currPage = Pages::StorageOfDataExplained;
            }
        }
        else if (currPage == Pages::StorageOfDataExplained)
        {
            const int gap = 12;
            const float colW = (midW - (2.0f * gap)) / 3.0f + 100;

            ClearBackground(WHITE);
            Text storageexplain("An Explaination of how Data is stored", 50, 40, 0, 0, 22, BLACK, MyFont, false);
            storageexplain.Render();

            Circle Audio("Audio", centerx - spacing / 2, (centery - spacing / 2) - 90, 40, 20, YELLOW, MyFont, false);
            Circle Image("Image", centerx + spacing / 2, (centery - spacing / 2) - 90, 40, 20, GREEN, MyFont, false);
            Circle GPS("GPS", centerx - spacing / 2, (centery + spacing / 2) - 90, 40, 20, BLUE, MyFont, false);
            Circle Video("Video", centerx + spacing / 2, (centery + spacing / 2) - 90, 40, 20, RED, MyFont, false);

            Text Middle("Software groups incoming streams into variable-sized blocks\nthat automatically adjust their size and detail based on scene activity.\nEach block is then stamped with time, location, and camera ID metadata\nso the system can easily sort and retrieve it later.", midX, midY, 600, 90, 16, BLACK, MyFont, false);
            Text ExplainationLeft("Live Storage:\nHolds active, recent data blocks.", midX - 300, boxY, colW, boxH, 12, BLACK, MyFont, false);
            Text ExplainationMiddle("Encrypted Archive:\nStores older data blocks\nin a secure,\nencrypted format.", midX + colW + gap - 100, boxY + 50, colW, boxH, 12, BLACK, MyFont, false);
            Text ExplainationRight("Auto-Purge:\nDeletes data blocks after a set retention\nperiod to manage\nstorage space.", midX + 2 * (colW + gap) - 20, boxY, colW, boxH, 12, BLACK, MyFont, false);

            Audio.Render();
            Image.Render();
            GPS.Render();
            Video.Render();
            Middle.Render();
            ExplainationLeft.Render();
            ExplainationMiddle.Render();
            ExplainationRight.Render();

            Connector(Middle, ExplainationLeft, Side::Bottom, Side::Top).DrawConnector();
            Connector(Middle, ExplainationMiddle, Side::Bottom, Side::Top).DrawConnector();
            Connector(Middle, ExplainationRight, Side::Bottom, Side::Top).DrawConnector();

            goToMainButton.Render();
            Explaination.Render();

            if (goToMainButton.Clicked())
            {
                currPage = Pages::StorageOfData;
            }
            if (Explaination.Clicked())
            {
                currPage = Pages::StorageOfDataExplained;
            }
        }
        else if (PredictionsButton.Clicked())
        {
            currPage = Pages::Predictions;
        }
        else if (currPage == Pages::Predictions)
        {

            ClearBackground(WHITE);
            Text("Predictive Policing & Feedback Loops\n click Visualize to see a visualization of predictive policing", 50, 40, 0, 0, 22, BLACK, MyFont, false).Render();

            Text predictiveAI("Predictive AI Policing", 100, 100, 250, 60, 18, BLACK, MyFont, false);
            Text predictiveAI2("Bias & Feedback Loops", 100, 350, 250, 60, 18, BLACK, MyFont, false);
            Text predictiveAI3("Broader Surveillance", 100, 600, 250, 60, 18, BLACK, MyFont, false);

            Text ExplainPredictiveAI("The software took historical crime\n incident reports and generated daily\n predictions of where and when certain crimes might happen.", 600, 95, 400, 70, 16, BLACK, MyFont, false);
            Text ExplainPredictiveAI2("Earlier investigations cited in the piece found\nthat Geolitica disproportionately targeted low-income,\nBlack, and Latino neighborhoods.", 600, 345, 400, 70, 16, BLACK, MyFont, false);
            Text ExplainPredictiveAI3("Surveillance and law enforcement platforms\nare expanding into broader data\nand patrol-management systems.", 600, 595, 400, 70, 16, BLACK, MyFont, false);

            predictiveAI.Render();
            predictiveAI2.Render();
            predictiveAI3.Render();

            ExplainPredictiveAI.Render();
            ExplainPredictiveAI2.Render();
            ExplainPredictiveAI3.Render();

            Connector connector1(predictiveAI, ExplainPredictiveAI, Side::Right, Side::Left);
            Connector connector2(predictiveAI2, ExplainPredictiveAI2, Side::Right, Side::Left);
            Connector connector3(predictiveAI3, ExplainPredictiveAI3, Side::Right, Side::Left);

            connector1.DrawConnector();
            connector2.DrawConnector();
            connector3.DrawConnector();

            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }
            VisualizePredictionsButton.Render();
            if (VisualizePredictionsButton.Clicked())
            {
                currPage = Pages::VisualizePredictions;
            }
        }
        else if (currPage == Pages::VisualizePredictions)
        {

            ClearBackground(WHITE);

            Text("Visualizing Predictive Policing", 50, 40, 0, 0, 22, BLACK, MyFont, false).Render();
            DrawTextureEx(predictionstex, (Vector2){screenWidth / 2 - predictionstex.width / 2, screenHeight / 2 - predictionstex.height / 2}, 0.0f, 1.0f, WHITE);
            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Predictions;
            }
        }

        if (Dashboard.Clicked())
        {
            currPage = Pages::Dashboard;
        }

        else if (currPage == Pages::Dashboard)
        {
            ClearBackground(WHITE);

            Text DASHINTRO(
                "Domain Awareness System (DAS) Overview.",
                30, 20, 0, 0, 20, BLACK, MyFont, false);
            Text ClickToVisualize("Click Visualize to see a visualization of the DAS Operations Room", 30, 60, 0, 0, 13, BLACK, MyFont, false);
            ClickToVisualize.Render();
            DASHINTRO.Render();

            Text DASH1("What is DAS?", 100, 100, 250, 60, 18, BLACK, MyFont, false);
            Text DASH2("How It Was Built:", 100, 350, 250, 60, 18, BLACK, MyFont, false);
            Text DASH3("Financial Arrangement:", 100, 600, 250, 60, 18, BLACK, MyFont, false);

            Text DASHEXPLAIN1(" The DAS is the largest digital surveillance system in the world\n is part of the Lower Manhattan Security Initiative\n and is used by the NYPD to monitor the city.", 600, 95, 600, 70, 16, BLACK, MyFont, false);

            Text DASHEXPLAIN2("Developed by combining NYPD officers' operational experience\n with Microsoft's technical expertise.", 600, 345, 500, 70, 16, BLACK, MyFont, false);

            Text DASHEXPLAIN3("The NYPD is to receive 30 percent of revenue from sales of DAS\n to other customers worldwide.", 600, 595, 550, 80, 16, BLACK, MyFont, false);

            DASH1.Render();
            DASH2.Render();
            DASH3.Render();

            DASHEXPLAIN1.Render();
            DASHEXPLAIN2.Render();
            DASHEXPLAIN3.Render();

            Connector connector1(DASH1, DASHEXPLAIN1, Side::Right, Side::Left);
            Connector connector2(DASH2, DASHEXPLAIN2, Side::Right, Side::Left);
            Connector connector3(DASH3, DASHEXPLAIN3, Side::Right, Side::Left);

            connector1.DrawConnector();
            connector2.DrawConnector();
            connector3.DrawConnector();

            goToMainButton.Render();

            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }

            VisualizePredictionsButton.Render();

            if (VisualizePredictionsButton.Clicked())
            {
                currPage = Pages::DASHBOARDVISUALIZE;
            }
        }

        else if (currPage == Pages::DASHBOARDVISUALIZE)
        {
            ClearBackground(WHITE);

            // Draw image first, scaled down
            DrawTextureEx(
                DAS,
                (Vector2){
                    screenWidth / 2.0f - DAS.width * 1.0f / 2.0f,
                    screenHeight / 2.0f - DAS.height * 1.0f / 2.0f},
                0.0f,
                1.0f,
                WHITE);

            Text DASHBOARDVISUALIZEINTRO("DAS Operations Room Visualization", 50, 30, 0, 0, 24, BLACK, MyFont, false);

            DASHBOARDVISUALIZEINTRO.Render();

            goToMainButton.Render();

            if (goToMainButton.Clicked())
            {
                currPage = Pages::Dashboard;
            }
        }
        if (currPage == Pages::InteractiveGame)
        {
            ClearBackground(RAYWHITE);
            // used https://www.raylib.com/examples.html  raylib examples to learn how to use the library and implement the interactive game

            if (IsKeyPressed(KEY_H))
            {
                if (IsCursorHidden())
                    ShowCursor();
                else
                    HideCursor();
            }

            // Optional reset key 'R' to clear spotted flags
            if (IsKeyPressed(KEY_R))
            {
                for (int i = 0; i < manhattanSpotCount; i++)
                {
                    manhattanSpots[i].spotted = false;
                }
                statusColor = SKYBLUE;
                statusBanner = "Reset spotted flags. Move cursor over Manhattan neighborhoods to scan again.";
            }

            ballPosition = GetMousePosition();

            // Optional cursor/scanner color changes (kept safe from accidentally firing when clicking BACK)
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
                ballColor = LIME;
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
                ballColor = DARKBLUE;
            else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE))
                ballColor = PURPLE;
            else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA))
                ballColor = YELLOW;
            else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD))
                ballColor = ORANGE;
            else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK))
                ballColor = BEIGE;

            // Fit manhattanmap.jpg proportionally in the center of the 1200x800 screen
            Rectangle mapArea = {340.0f, 25.0f, 520.0f, 655.0f};
            Rectangle mapRect = mapArea;
            if (manhattanMap.id != 0 && manhattanMap.width > 0 && manhattanMap.height > 0)
            {
                float scaleX = mapArea.width / static_cast<float>(manhattanMap.width);
                float scaleY = mapArea.height / static_cast<float>(manhattanMap.height);
                float scale = (scaleX < scaleY) ? scaleX : scaleY;

                float drawW = manhattanMap.width * scale;
                float drawH = manhattanMap.height * scale;
                mapRect = {
                    mapArea.x + (mapArea.width - drawW) * 0.5f,
                    mapArea.y + (mapArea.height - drawH) * 0.5f,
                    drawW,
                    drawH};

                DrawTexturePro(
                    manhattanMap,
                    {0.0f, 0.0f, static_cast<float>(manhattanMap.width), static_cast<float>(manhattanMap.height)},
                    mapRect,
                    {0.0f, 0.0f},
                    0.0f,
                    WHITE);
            }

            // Check spotting on every Manhattan neighborhood node
            float spotRadius = 24.0f;
            for (int i = 0; i < manhattanSpotCount; i++)
            {
                Vector2 pt = {
                    mapRect.x + mapRect.width * manhattanSpots[i].u,
                    mapRect.y + mapRect.height * manhattanSpots[i].v};

                float dx = ballPosition.x - pt.x;
                float dy = ballPosition.y - pt.y;
                bool inSpotRange = (dx * dx + dy * dy) <= (spotRadius * spotRadius);

                if (inSpotRange && !manhattanSpots[i].spotted)
                {
                    manhattanSpots[i].spotted = true;

                    if (manhattanSpots[i].isFlaggedArea)
                    {
                        ballColor = RED;
                        statusColor = RED;
                        statusBanner = TextFormat("RED ALERT: Neighborhood flagged for concentrated patrols and data collection (This is a Black neighborhood which reinforces bias in police predictions)");
                        PlaySound(alertSound);
                    }

                    else
                    {
                        ballColor = SKYBLUE;
                        statusColor = SKYBLUE;
                        statusBanner = TextFormat("BLUE ALERT: Neighborhood isn't targeted because it has a lower targeted flag in this simulation");
                    }
                }

                // Draw node marker on top of the map photo
                Color markerCol = (manhattanSpots[i].spotted && manhattanSpots[i].isFlaggedArea) ? RED : SKYBLUE;
                DrawCircleV(pt, 9.0f, markerCol);
                DrawCircleLines(static_cast<int>(pt.x), static_cast<int>(pt.y), 9.0f, BLACK);

                if (manhattanSpots[i].spotted)
                {
                    DrawCircleLines(static_cast<int>(pt.x), static_cast<int>(pt.y), 15.0f, markerCol);
                    DrawRectangle(static_cast<int>(pt.x) + 13, static_cast<int>(pt.y) - 20, 64, 15, markerCol);
                    DrawText("SPOTTED", static_cast<int>(pt.x) + 16, static_cast<int>(pt.y) - 18, 10, WHITE);
                }

                DrawText(manhattanSpots[i].name, static_cast<int>(pt.x) + 13, static_cast<int>(pt.y) - 2, 12, BLACK);
            }

            // Draw cursor/scanner circle
            DrawCircleV(ballPosition, 22.0f, Fade(ballColor, 0.35f));
            DrawCircleLines(static_cast<int>(ballPosition.x), static_cast<int>(ballPosition.y), 22.0f, ballColor);

            // Top-left instructions & cursor status
            DrawText("Biased Surveillance Simulator", 10, 10, 18, DARKGRAY);
            DrawText("Press 'H' to toggle cursor | 'R' to reset flags", 10, 32, 16, DARKGRAY);
            if (IsCursorHidden())
                DrawText("CURSOR HIDDEN", 10, 54, 16, RED);
            else
                DrawText("CURSOR VISIBLE", 10, 54, 16, DARKGREEN);

            // Bottom alert & bias/feedback-loop bar
            DrawRectangle(40, 700, 1120, 65, Color{20, 24, 34, 240});
            DrawRectangleLinesEx({40.0f, 700.0f, 1120.0f, 65.0f}, 2.0f, statusColor);
            DrawText(statusBanner, 55, 722, 15, statusColor);

            // Return to main infographic
            goToMainButton.Render();
            if (goToMainButton.Clicked())
            {
                currPage = Pages::Main;
            }
        }

        EndDrawing();
    }
    UnloadFont(MyFont);
    UnloadFont(interFont);
    UnloadTexture(predictionstex);
    UnloadSound(alertSound);
    UnloadTexture(photo);
    UnloadTexture(camerascrapped);
    UnloadTexture(facialtex);
    CloseWindow();
    UnloadTexture(manhattanMap);
    CloseAudioDevice();
    UnloadTexture(DAS);
    PlateRecognizer::Shutdown();
    return 0;
}
