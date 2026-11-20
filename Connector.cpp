#include "Connector.h"

Connector::Connector(Text startText, Text endText, Side startSide, Side endSide) : startText(startText), endText(endText), startSide(startSide), endSide(endSide) {}

void Connector::DrawConnector() {
    Vector2 startPos, endPos;

    float startX = static_cast<float>(startText.GetPosX());
    float startY = static_cast<float>(startText.GetPosY());
    float endX = static_cast<float>(endText.GetPosX());
    float endY = static_cast<float>(endText.GetPosY());

    switch (startSide) {
        case Side::Top:
            startPos = {startX + startText.GetWidth() / 2.0f, startY};
            break;
        case Side::Bottom:
            startPos = {startX + startText.GetWidth() / 2.0f, startY + startText.GetHeight()};
            break;
        case Side::Left:
            startPos = {startX, startY + startText.GetHeight() / 2.0f};
            break;
        case Side::Right:
            startPos = {startX + startText.GetWidth(), startY + startText.GetHeight() / 2.0f};
            break;
    }

    switch (endSide) {
        case Side::Top:
            endPos = {endX + endText.GetWidth() / 2.0f, endY};
            break;
        case Side::Bottom:
            endPos = {endX + endText.GetWidth() / 2.0f, endY + endText.GetHeight()};
            break;
        case Side::Left:
            endPos = {endX, endY + endText.GetHeight() / 2.0f};
            break;
        case Side::Right:
            endPos = {endX + endText.GetWidth(), endY + endText.GetHeight() / 2.0f};
            break;
    }

    DrawLineEx(startPos, endPos, 3.0f, BLACK);
}