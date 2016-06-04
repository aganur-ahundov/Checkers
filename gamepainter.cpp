#include "gamepainter.h"
#include <QImage>


void GamePainter::drawBlackCell( int _i, int _j )
{
    setBrush( QBrush( QColor( 103, 57, 35 ) ) );
    drawRect(
                _i * CELL_WIDTH,
                _j * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT
                );
}


void GamePainter::drawWhiteCell( int _i, int _j )
{
    setBrush( QBrush( QColor( 239, 222, 205 ) ) );
    drawRect(
                _i * CELL_WIDTH,
                _j * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT
                );
}



void GamePainter::drawBlackChecker( int _i, int _j )
{
    setBrush( QBrush( Qt::black ) );
    drawEllipse(
                _i * CELL_WIDTH,
                _j * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT
                );
}



void GamePainter::drawWhiteChecker( int _i, int _j )
{
    setBrush( QBrush( Qt::white ) );
    drawEllipse(
                _i * CELL_WIDTH,
                _j * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT
                );
}


void GamePainter::drawBlackKing( int _i, int _j )
{
    setBrush( QBrush( QColor( 200, 200, 200 ) ) );
    drawEllipse(
                _i * CELL_WIDTH + CELL_WIDTH/2,
                _j * CELL_HEIGHT + CELL_WIDTH/2,
                CELL_WIDTH,
                CELL_HEIGHT
                );
}


void GamePainter::drawWhiteKing( int _i, int _j )
{
    setBrush( QBrush( QColor( 50, 50 , 50 ) ) );
    drawEllipse(
                _i * CELL_WIDTH + CELL_WIDTH/2,
                _j * CELL_HEIGHT + CELL_WIDTH/2,
                CELL_WIDTH,
                CELL_HEIGHT
                );
}


void GamePainter::drawFrameForNextStep(int _i, int _j)
{
    setPen( QPen( Qt::blue, 5 ) );
    setBrush(QBrush( QColor( 103, 57, 35 ) ));
    drawRect(
                _i * CELL_WIDTH,
                _j * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT
                );

    setPen( Qt::black );
}
