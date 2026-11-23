#include "Connector.h"

Connector::Connector(const Text& startText, const Text& endText, Side startSide, Side endSide)
    : mode(TargetMode::TextMode),
      startText(startText),
      endText(endText),
      startCircle(),
      endCircle(),
      startSide(startSide),
      endSide(endSide) {}

Connector::Connector(const Circle& startCircle, const Circle& endCircle, Side startSide, Side endSide)
    : mode(TargetMode::CircleMode),
      startText(),
      endText(),
      startCircle(startCircle),
      endCircle(endCircle),
      startSide(startSide),
      endSide(endSide) {}

Vector2 Connector::GetAnchorPoint(const Text& target, Side side) const {
    float x = static_cast<float>(target.GetPosX());
    float y = static_cast<float>(target.GetPosY());
    float w = static_cast<float>(target.GetWidth());
    float h = static_cast<float>(target.GetHeight());

    switch (side) {
        case Side::Top:
            return { x + w / 2.0f, y };
        case Side::Bottom:
            return { x + w / 2.0f, y + h };
        case Side::Left:
            return { x, y + h / 2.0f };
        case Side::Right:
            return { x + w, y + h / 2.0f };
        default:
            return { x + w / 2.0f, y + h / 2.0f };
    }
}

Vector2 Connector::GetAnchorPoint(const Circle& target, Side side) const {
    float cx = static_cast<float>(target.GetposX());
    float cy = static_cast<float>(target.GetposY());
    float r  = static_cast<float>(target.GetRadius());

    switch (side) {
        case Side::Top:
            return { cx, cy - r };
        case Side::Bottom:
            return { cx, cy + r };
        case Side::Left:
            return { cx - r, cy };
        case Side::Right:
            return { cx + r, cy };
        default:
            return { cx, cy };
    }
}

void Connector::DrawConnector() {
    Vector2 startPos{};
    Vector2 endPos{};

    if (mode == TargetMode::TextMode) {
        startPos = GetAnchorPoint(startText, startSide);
        endPos   = GetAnchorPoint(endText, endSide);
    } else {
        startPos = GetAnchorPoint(startCircle, startSide);
        endPos   = GetAnchorPoint(endCircle, endSide);
    }

    DrawLineEx(startPos, endPos, 3.0f, BLACK);
}
