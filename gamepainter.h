#ifndef GAMEPAINTER_H
#define GAMEPAINTER_H

#include <QPainter>

class GamePainter : public QPainter
{
    static const int CELL_WIDTH  = 100;
    static const int CELL_HEIGHT = 100;


public:
    void drawWhiteCell   ( int _i, int _j );
    void drawBlackCell   ( int _i, int _j );
    void drawWhiteChecker( int _i, int _j );
    void drawBlackChecker( int _i, int _j );
    void drawWhiteKing   ( int _i, int _j );
    void drawBlackKing   ( int _i, int _j );

};

#endif // GAMEPAINTER_H
