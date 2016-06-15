#ifndef GAMEPAINTER_H
#define GAMEPAINTER_H

#include <QPainter>
#include <Qpixmap>

class GamePainter : public QPainter
{
    static const int CELL_WIDTH  = 95;
    static const int CELL_HEIGHT = 95;


public:
    void drawWhiteCell       ( int _i, int _j );
    void drawBlackCell       ( int _i, int _j );
    void drawWhiteChecker    ( int _i, int _j );
    void drawBlackChecker    ( int _i, int _j );
    void drawWhiteKing       ( int _i, int _j );
    void drawBlackKing       ( int _i, int _j );
    void drawFrameForNextStep( int _i, int _j );

    GamePainter();

private:

    QPixmap m_black_checker;
    QPixmap m_white_checker;
    QPixmap m_black_king;
    QPixmap m_white_king;

};

#endif // GAMEPAINTER_H
