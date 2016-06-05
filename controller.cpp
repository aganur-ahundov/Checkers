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
            if( m_board->m_board[i][j] == Board::TYPE_NEXT_STEP
                    || m_board->m_board[i][j] == Board::TYPE_BEAT)
                m_board->m_board[i][j] = Board::TYPE_BLACK;
}


void Controller::whiteToMove(int _i, int _j )
{
    unselect();          //убираем все выделения

    if( whiteToBeat( _i, _j ) == false )
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

    is_selected = true;  //ставим флаг, да бы не сбились выделения в конце функции selected

    }
}

void Controller::blackToMove(int _i, int _j)
{
    unselect();          //убираем все выделения

    if( blackToBeat(_i, _j) == false )
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


        is_selected = true;  //ставим флаг, да бы не сбились выделения в конце функции selected

    }
}


bool Controller::whiteToBeat(int _i, int _j)
{

    bool need_to_beat = false; //если есть, что ударить. других ходов быть не может.

    //бить вперед
    if( m_board->m_board[ _i - 1 ][ _j + 1 ] == Board::TYPE_BLACK_CHECKER
                && m_board->m_board[ _i - 2 ][ _j + 2 ] == Board::TYPE_BLACK )
       {
         m_board->m_board[ _i - 2 ][ _j + 2 ] = Board::TYPE_BEAT;
         is_selected = true;
         need_to_beat = true;
       }

    if( m_board->m_board[ _i - 1 ][ _j - 1 ] == Board::TYPE_BLACK_CHECKER
                 && m_board->m_board[ _i - 2 ][ _j - 2 ] == Board::TYPE_BLACK )
        {
          m_board->m_board[ _i - 2 ][ _j - 2 ] = Board::TYPE_BEAT;
          is_selected = true;
          need_to_beat = true;
        }

    //Проверям врагов в округе сзади
    if( m_board->m_board[ _i + 1 ][ _j - 1 ] == Board::TYPE_BLACK_CHECKER
             && m_board->m_board[ _i + 2 ][ _j - 2 ] == Board::TYPE_BLACK )
    {
      m_board->m_board[ _i + 2 ][ _j - 2 ] = Board::TYPE_BEAT;
      is_selected = true;
      need_to_beat = true;
    }

    if( m_board->m_board[ _i + 1 ][ _j + 1 ] == Board::TYPE_BLACK_CHECKER
             && m_board->m_board[ _i + 2 ][ _j + 2 ] == Board::TYPE_BLACK )
    {
      m_board->m_board[ _i + 2 ][ _j + 2 ] = Board::TYPE_BEAT;
      is_selected = true;
      need_to_beat = true;
    }

    return need_to_beat;
}


bool Controller::blackToBeat(int _i, int _j)
{
    bool need_to_beat = false; //если есть, что ударить. других ходов быть не может.

    //проверяем врагов спереди
    if( m_board->m_board[ _i + 1 ][ _j - 1 ] == Board::TYPE_WHITE_CHECKER
                        && m_board->m_board[ _i + 2 ][ _j - 2 ] == Board::TYPE_BLACK )
            {
               m_board->m_board[ _i + 2 ][ _j - 2 ] = Board::TYPE_BEAT;
               is_selected = true;
               need_to_beat = true;
            }
    if( m_board->m_board[ _i + 1 ][ _j + 1 ] == Board::TYPE_WHITE_CHECKER
                     && m_board->m_board[ _i + 2 ][ _j + 2 ] == Board::TYPE_BLACK )
            {
              m_board->m_board[ _i + 2 ][ _j + 2 ] = Board::TYPE_BEAT;
              is_selected = true;
              need_to_beat = true;
            }


    //проверяем врагов сзади
    if( m_board->m_board[ _i - 1 ][ _j + 1 ] == Board::TYPE_WHITE_CHECKER
                     && m_board->m_board[ _i - 2 ][ _j + 2 ] == Board::TYPE_BLACK )
            {
              m_board->m_board[ _i - 2 ][ _j + 2 ] = Board::TYPE_BEAT;
              is_selected = true;
              need_to_beat = true;
            }

    if( m_board->m_board[ _i - 1 ][ _j - 1 ] == Board::TYPE_WHITE_CHECKER
                       && m_board->m_board[ _i - 2 ][ _j - 2 ] == Board::TYPE_BLACK )
           {
              m_board->m_board[ _i - 2 ][ _j - 2 ] = Board::TYPE_BEAT;
              is_selected = true;
              need_to_beat = true;
           }

    return need_to_beat;
}


void Controller::selected(int _i, int _j)
{
        //если ходят белые, то
        if ( white_moving == true )
        {
            //если мы успешно выбрали белую шашку
            if ( m_board->m_board[_i][_j] == Board::TYPE_WHITE_CHECKER )
                whiteToMove(_i, _j); //выделяем все клеточки куда можно ходить
            else
                is_selected = false;
        }
        else //если ходят черные
        {
            //если мы успешно выбрали черную шашку
            if ( m_board->m_board[_i][_j] == Board::TYPE_BLACK_CHECKER )
               blackToMove(_i, _j); //выделяем все клеточки куда можно ходить
            else
                is_selected = false; //если промахнулись, то убираем все выделения
        }

        //если мы ходим
        if( m_board->m_board[_i][_j] == Board::TYPE_NEXT_STEP )
            move_checker(_i, _j);
        //если бьем
        else if ( m_board->m_board[_i][_j] == Board::TYPE_BEAT )
             beat( _i, _j );


        m_currI = _i;   //запоминаем координаты, что бы потом осуществить ход
        m_currJ = _j;

        //что бы не висели не нужные выделения
        if( is_selected == false )
            unselect();

        //перересуем доску
      emit m_board->repaint();
}


void Controller::move_checker(int _i, int _j)
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


void Controller::beat(int _i,  int _j)
{
    unselect();

    //если ходим белыми
   if( white_moving )
   {
       //меняем местами состояния
       m_board->m_board[_i][_j] = Board::TYPE_WHITE_CHECKER;
       m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       removeTheBattered(_i, _j);
       m_currI = _i;
       m_currJ = _j;
       whiteToBeat( _i, _j );
   }
   else
   {
       //тоже самое для черных
       m_board->m_board[_i][_j] = Board::TYPE_BLACK_CHECKER;
       m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       removeTheBattered(_i,_j);
       m_currI = _i;
       m_currJ = _j;
       blackToBeat( _i, _j );
   }

   if(is_selected == false)
    white_moving = !white_moving;  //даем ход противнику
   // is_selected = false;
}


void Controller::removeTheBattered(int _i, int _j)
{
    if( _j > m_currJ && _i < m_currI )
        m_board->m_board[m_currI - 1][ m_currJ + 1 ] = Board::TYPE_BLACK;

    else if( _j < m_currJ && _i < m_currI )
        m_board->m_board[m_currI - 1][ m_currJ - 1 ] = Board::TYPE_BLACK;

    else if( _j > m_currJ && _i > m_currI )
        m_board->m_board[m_currI + 1][ m_currJ + 1 ] = Board::TYPE_BLACK;

    else if( _j < m_currJ && _i > m_currI )
        m_board->m_board[m_currI + 1][ m_currJ - 1 ] = Board::TYPE_BLACK;


    if( white_moving )
        --m_blackCount;
    else
        --m_whiteCount;
}
