#include "controller.h"
#include <QApplication>
#include <QPaintEvent>
#include "board.h"

Controller::Controller( QWidget* _parent )
    :QWidget( _parent )
{
    //у игроков по 12 шашек в начале
  m_blackCount = 12;
  m_whiteCount = 12;

  //задаем координаты, которых нет на доске
  m_currI = -1;
  m_currJ = -1;

   //начинают белые, ни одна из шашек не выделена
  white_moving = true;
  is_selected  = false;

  m_board = new Board;

  //обрабатываем нажатие мыши по окну
  connect( m_board, SIGNAL(clicked(int,int)), SLOT(selected(int,int)) );

}


Controller::~Controller()
{
    delete m_board;
}


void Controller::start_game()
{
    //делаем это в функции начало игры, так как этого достаточно, что бы начать
    m_board->show();
}

void Controller::show()
{
    m_board->show(); //выводим виджет-доску
}


void Controller::unselect()
{
    //убираем все выделения с доски
    for(int i = 0; i < m_board->BOARD_HEIGHT; i++)
        for( int j = 0; j < m_board->BOARD_WIDTH; j++ )
            if( m_board->m_board[i][j] == Board::TYPE_NEXT_STEP )
                m_board->m_board[i][j] = Board::TYPE_BLACK;
}


void Controller::whiteToMove(int _i, int _j )
{
    //проверяем пустые ли клеточки, для хода
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
    //проверяем пустые ли клеточки, для хода
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
    //если ходят белые, то
    if ( white_moving == true )
    {
        //если мы успешно выбрали белую шашку
        if ( m_board->m_board[_i][_j] == Board::TYPE_WHITE_CHECKER )
        {
           unselect();          //убираем все выделения
           whiteToMove(_i, _j); //выделяем все клеточки куда можно ходить
           is_selected = true;  //ставим флаг, да бы не сбились выделения в конце функции
        }
        else
            is_selected = false;
    }
    else //если ходят черные
    {
        //если мы успешно выбрали черную шашку
        if ( m_board->m_board[_i][_j] == Board::TYPE_BLACK_CHECKER )
        {
           unselect();          //убираем все выделения
           blackToMove(_i, _j); //выделяем все клеточки куда можно ходить
           is_selected = true;  //ставим флаг, да бы не сбились выделения в конце функции
        }
        else
            is_selected = false; //если промахнулись, то убираем все выделения
    }

    //если мы походили
    if( m_board->m_board[_i][_j] == Board::TYPE_NEXT_STEP )
    {
        //если ходим белыми
       if( white_moving )
       {
           //меняем местами состояния
           m_board->m_board[_i][_j] = Board::TYPE_WHITE_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;

       }
       else
       {
           //тоже самое для черных
           m_board->m_board[_i][_j] = Board::TYPE_BLACK_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
        white_moving = !white_moving;  //даем ход противнику
        is_selected = false;
    }



    m_currI = _i;   //запоминаем координаты, что бы потом осуществить ход
    m_currJ = _j;

    //что бы не висели не нужные выделения
    if(is_selected == false)
        unselect();

    //перересуем доску
  emit m_board->repaint();
}
