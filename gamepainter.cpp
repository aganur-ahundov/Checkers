#include "gamepainter.h"
#include <QImage>


GamePainter::GamePainter()
{
    m_black_checker.load( "../Checkers_v2/resources/black_checker.png" );
    Q_ASSERT( m_black_checker.isNull() == false );
    m_black_checker = m_black_checker.scaled( 100,100 );

    m_black_king.load( "../Checkers_v2/resources/black_king.png" );
    Q_ASSERT( m_black_king.isNull() == false );
    m_black_king = m_black_king.scaled( 100, 100 );

    m_white_checker.load( "../Checkers_v2/resources/white_checker.png" );
    Q_ASSERT( m_white_checker.isNull() == false );
    m_white_checker = m_white_checker.scaled( 100, 100 );

    m_white_king.load( "../Checkers_v2/resources/white_king.png" );
    Q_ASSERT( m_white_king.isNull() == false );
    m_white_king = m_white_king.scaled( 100, 100 );
}

void GamePainter::drawBlackCell( int _i, int _j )
{
//    setBrush( QBrush( QColor( 103, 57, 35 ) ) );
//    drawRect(
//                _i * CELL_WIDTH,
//                _j * CELL_HEIGHT,
//                CELL_WIDTH,
//                CELL_HEIGHT
//                );
}


void GamePainter::drawWhiteCell( int _i, int _j )
{
//    setBrush( QBrush( QColor( 239, 222, 205 ) ) );
//    drawRect(
//                _i * CELL_WIDTH,
//                _j * CELL_HEIGHT,
//                CELL_WIDTH,
//                CELL_HEIGHT
//                );
}



void GamePainter::drawBlackChecker( int _i, int _j )
{
//    setBrush( QBrush( Qt::black ) );
//    drawEllipse(
//                _i * CELL_WIDTH,
//                _j * CELL_HEIGHT,
//                CELL_WIDTH,
//                CELL_HEIGHT
//                );
    drawPixmap( _i * CELL_WIDTH + 20,
                _j * CELL_HEIGHT + 20,
                CELL_WIDTH,
                CELL_HEIGHT,
                m_black_checker );
}



void GamePainter::drawWhiteChecker( int _i, int _j )
{/*
    setBrush( QBrush( Qt::white ) );
    drawEllipse(*/
    drawPixmap(
                _i * CELL_WIDTH + 20,
                _j * CELL_HEIGHT + 25,
                CELL_WIDTH,
                CELL_HEIGHT,
                m_white_checker
                );
}


void GamePainter::drawBlackKing( int _i, int _j )
{/*
    setBrush( QBrush( QColor( 200, 200, 200 ) ) );
    drawEllipse(
                _i * CELL_WIDTH,
                _j * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT
                );*/
    drawPixmap(
                _i * CELL_WIDTH + 20,
                _j * CELL_HEIGHT + 25,
                CELL_WIDTH,
                CELL_HEIGHT,
                m_black_king
                );
}


void GamePainter::drawWhiteKing( int _i, int _j )
{
   // setBrush( QBrush( QColor( 50, 50 , 50 ) ) );
   // drawEllipse(
    drawPixmap(
                _i * CELL_WIDTH + 20,
                _j * CELL_HEIGHT + 25,
                CELL_WIDTH,
                CELL_HEIGHT,
                m_white_king
                );
}


void GamePainter::drawFrameForNextStep(int _i, int _j)
{
    setPen( QPen( Qt::red, 5 ) );
    //setBrush(QBrush( QColor( 103, 57, 35 ) ));
    setBrush( QBrush(Qt::NoBrush) );
    drawRect(
                _i * CELL_WIDTH + 20,
                _j * CELL_HEIGHT + 25,
                CELL_WIDTH,
                CELL_HEIGHT
                );

    setPen( Qt::black );
}
