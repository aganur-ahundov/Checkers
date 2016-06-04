#include "gamepainter.h"
#include <QImage>


void GamePainter::drawBlackCell( int _i, int _j )
{
    setBrush( QBrush( Qt::black ) );
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


//QImage GamePainter::createImageBG()
//{
//   QImage sourceImage( QSize(CELL_WIDTH, CELL_HEIGHT), QImage::Format_ARGB32_Premultiplied  );
//   return sourceImage;
//}

//QLabel GamePainter::drawChecker(int _i, int _j, Board::Cell _t)
//{
//    QImage source_cell = m_painter.createImageBG();
//    m_painter.begin( &source_cell );
//    m_painter.setRenderHint( QPainter::Antialiasing, true );


//    m_painter.drawBlackCell( i, j );
//    m_painter.end();

//    QImage result_cell = m_painter.createImageBG();
//    m_painter.begin( result_cell );
//    m_painter.setRenderHint( QPainter::Antialiasing, true );
//    m_painter.setCompositionMode( QPainter );
//}
