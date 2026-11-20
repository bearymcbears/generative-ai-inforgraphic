#ifndef CONNECTOR
#define CONNECTOR
#include "Text.h"

enum class Side {Top, Bottom, Left, Right};

class Connector {
    public:
        Connector(Text startText, Text endText, Side startSide, Side endSide);
        void DrawConnector();
    private:
        Text startText;
        Text endText;
        Side startSide;
        Side endSide;
};


#endif 