#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Text.h"
#include "Circle.h"

enum class Side { Top, Bottom, Left, Right };

class Connector {
public:
    Connector(const Text& startText, const Text& endText, Side startSide, Side endSide);
    Connector(const Circle& startCircle, const Circle& endCircle, Side startSide, Side endSide);
    Connector(const Circle& startCircle, const Circle& endCircle);

    void DrawConnector();

private:
    enum class TargetMode { TextMode, CircleMode };

    TargetMode mode;
    Text startText;
    Text endText;
    Circle startCircle;
    Circle endCircle;
    Side startSide;
    Side endSide;

    Vector2 GetAnchorPoint(const Text& target, Side side) const;
    Vector2 GetAnchorPoint(const Circle& target, Side side) const;
};

#endif
