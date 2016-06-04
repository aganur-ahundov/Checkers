#include "controller.h"
#include <QApplication>
#include <QPaintEvent>
#include "board.h"

Controller::Controller( QWidget* _parent )
    :QWidget( _parent )
{
  m_blackCount = 12;
  m_whiteCount = 12;

  m_currI = -1;
  m_currJ = -1;

  white_moving = true;
  is_selected  = false;

  m_board = new Board;


  connect( m_board, SIGNAL(clicked(int,int)), SLOT(selected(int,int)) );

}


Controller::~Controller()
{
    delete m_board;
}


void Controller::start_game()
{

}


//void Controller::whiteToMove( )
//{
//}
void Controller::show()
{
    m_board->show();
}

void Controller::unselect()
{
    for(int i = 0; i < m_board->BOARD_HEIGHT; i++)
        for( int j = 0; j < m_board->BOARD_WIDTH; j++ )
            if( m_board->m_board[i][j] == Board::TYPE_NEXT_STEP )
                m_board->m_board[i][j] = Board::TYPE_BLACK;
}


void Controller::whiteToMove(int _i, int _j )
{
    if( m_board->m_board[ _i - 1 ][ _j - 1 ] == Board::TYPE_BLACK )
      {
        m_board->m_board[ _i - 1 ][ _j - 1 ] = Board::TYPE_NEXT_STEP;
      }
    if( m_board->m_board[ _i - 1 ][ _j + 1 ] == Board::TYPE_BLACK )
      {
        m_board->m_board[ _i - 1 ][ _j + 1 ] = Board::TYPE_NEXT_STEP;
      }
}


void Controller::blackToMove(int _i, int _j)
{
        if( m_board->m_board[ _i + 1 ][ _j - 1 ] == Board::TYPE_BLACK )
          {
            m_board->m_board[ _i + 1 ][ _j - 1 ] = Board::TYPE_NEXT_STEP;
          }
        if( m_board->m_board[ _i + 1 ][ _j + 1 ] == Board::TYPE_BLACK )
          {
            m_board->m_board[ _i + 1 ][ _j + 1 ] = Board::TYPE_NEXT_STEP;
          }
}


void Controller::selected(int _i, int _j)
{
    if ( white_moving == true )
    {
        if ( m_board->m_board[_i][_j] == Board::TYPE_WHITE_CHECKER )
        {
           unselect();
           whiteToMove(_i, _j);
           is_selected = true;
        }
        else
            is_selected = false;
    }
    else
    {
        if ( m_board->m_board[_i][_j] == Board::TYPE_BLACK_CHECKER )
        {
           unselect();
           blackToMove(_i, _j);
           is_selected = true;
        }
        else
            is_selected = false;
    }


    if( m_board->m_board[_i][_j] == Board::TYPE_NEXT_STEP )
    {
       if( white_moving )
       {
           m_board->m_board[_i][_j] = Board::TYPE_WHITE_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;

       }
       else
       {
           m_board->m_board[_i][_j] = Board::TYPE_BLACK_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
        white_moving = !white_moving;
        is_selected = false;
    }



    m_currI = _i;
    m_currJ = _j;

    if(is_selected == false)
        unselect();

  emit m_board->repaint();
}
