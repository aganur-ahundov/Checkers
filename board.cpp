#include "board.h"
#include <vector>
#include <QMouseEvent>
#include <QMessageBox>




Board::Board(QWidget *parent)
    : QWidget(parent)
{

   restart();
   setFixedSize( 800, 800 );

   QPalette p;
   QPixmap pm("../Checkers_v2/resources/Board.png");
   pm = pm.scaled( 1415, 900 );
   p.setBrush( this->backgroundRole(), QBrush( pm ) );

   setPalette(p);

}


void Board::restart()
{
    //задаем начальное состояние доски
   for ( int i = 0; i < BOARD_WIDTH; i++ )
   {
       for ( int j = 0; j < BOARD_HEIGHT; j++ )
       {
           m_board[i][j] = TYPE_BLACK;
               if (  ( (i + 1) + (j + 1) )%2 == 0  )
               {
                   if( i < 3 )
                     m_board[i][j] = TYPE_BLACK_CHECKER;
                   else if ( i > 4 )
                     m_board[i][j] = TYPE_WHITE_CHECKER;
               }
               else
                   m_board[i][j] = TYPE_WHITE;
       }
   }
}

void Board::mousePressEvent(QMouseEvent *_e)
{
    int i = _e->x()/100;
    int j = _e->y()/100;

    emit clicked( j, i );

}

void Board::keyPressEvent(QKeyEvent *_e)
{
    if( _e->key() == Qt::Key_Escape );
        //emit menu();
}

void Board::paintEvent( QPaintEvent* _e )
{

    //рисуем. все просто
    m_painter.begin( this );
    m_painter.setRenderHint( QPainter::Antialiasing, true );
    for( int i = 0; i < BOARD_WIDTH; i++ )
    {
        for( int j = 0; j < BOARD_HEIGHT; j++ )
        {
            switch ( m_board[j][i]  )
            {
            case TYPE_BLACK:;
                break;
            case TYPE_WHITE:
                break;
            case TYPE_BLACK_CHECKER:
                m_painter.drawBlackChecker( i, j );
                break;
            case TYPE_BLACK_KING:
                m_painter.drawBlackKing( i, j );
                break;
            case TYPE_WHITE_CHECKER:
                m_painter.drawWhiteChecker( i, j );
                break;
            case TYPE_WHITE_KING:
                m_painter.drawWhiteKing( i, j );
                break;
            case TYPE_NEXT_STEP:
                m_painter.drawFrameForNextStep( i, j );
                break;
            case TYPE_BEAT:
                m_painter.drawFrameForNextStep( i, j );
                break;
            default:
                Q_ASSERT ( 0 );
                break;
            }
        }
    }

    m_painter.end();
}
