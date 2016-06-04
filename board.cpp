#include "board.h"
#include <vector>
#include <QMouseEvent>
#include <QMessageBox>







Board::Board(QWidget *parent)
    : QWidget(parent)
{
   for ( int i = 0; i < BOARD_WIDTH; i++ )
   {
       for ( int j = 0; j < BOARD_HEIGHT; j++ )
       {
               if (  ( (i + 1) + (j + 1) )%2 == 0  )
               {

                   if( i < 3 )
                     m_board[i][j] = TYPE_BLACK_CHECKER;
                   else if ( i > 4 )
                     m_board[i][j] = TYPE_WHITE_CHECKER;
                   else
                     m_board[i][j] = TYPE_BLACK;
               }
               else
                   m_board[i][j] = TYPE_WHITE;
       }
   }

   QPalette p;
   p.setBrush( this->backgroundRole(), QBrush( QColor( 103, 57, 35 ) ) );
   setPalette(p);

   resize( 800, 800 );
}


void Board::mousePressEvent(QMouseEvent *_e)
{
    int x = _e->x()/100;
    int y = _e->y()/100;

}


void Board::paintEvent( QPaintEvent* _e )
{

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
                m_painter.drawWhiteCell( i, j);
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
            default:
                Q_ASSERT ( 0 );
                break;
            }
        }
    }

    m_painter.end();
}
