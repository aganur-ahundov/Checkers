#include "controller.h"
#include <QApplication>
#include <QPaintEvent>
#include "board.h"
#include <QMessageBox>
#include <QKeyEvent>


Controller::Controller( QWidget* _parent )
    :QWidget( _parent )
{
        //у игроков по 12 шашек в начале
      m_blackCount = 12;
      m_whiteCount = 1;

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

void Controller::hide()
{
    m_board->hide();
}


Controller::~Controller()
{
    delete m_board;
}

void Controller::restart()
{
    m_board->restart();
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


bool Controller::check_board_for_battle()
{
    for( int i = 0; i < m_board->BOARD_HEIGHT; i++ )
    {
        for( int j = 0; j < m_board->BOARD_WIDTH; j++ )
        {
            if ( white_moving && m_board->m_board[i][j] == Board::TYPE_WHITE_CHECKER )
            {
                if ( whiteToBeat( i, j ) )
                    return true;
            }
            else if ( white_moving == false && m_board->m_board[i][j] == Board::TYPE_BLACK_CHECKER  )
            {
                if ( blackToBeat( i,j ) )
                    return true;
            }
            else if( m_board->m_board[i][j] == Board::TYPE_WHITE_KING && white_moving )
            {
                if( king_can_beat( i, j ) )
                    return true;
            }
            else if( m_board->m_board[i][j] == Board::TYPE_BLACK_KING && white_moving == false )
            {
                if( king_can_beat( i, j ) )
                    return true;
            }
        }
    }
    return false;
}





void Controller::setAllNewStepsByAllDirections( int _i, int _j )
{
    int i = _i + 1;
    int j = _j - 1;

    while( m_board->m_board[i][j] == Board::TYPE_BLACK
           && i < m_board->BOARD_HEIGHT
           && j >= 0)
    {
        m_board->m_board[i][j] = Board::TYPE_NEXT_STEP;

        ++i;
        --j;


    }



    i = _i + 1;
    j = _j + 1;

    while( m_board->m_board[i][j] == Board::TYPE_BLACK
           && i < m_board->BOARD_HEIGHT
           && j < m_board->BOARD_WIDTH)
    {
            m_board->m_board[i][j] = Board::TYPE_NEXT_STEP;

        ++i;
        ++j;
    }



    i = _i - 1;
    j = _j - 1;

    while( m_board->m_board[i][j] == Board::TYPE_BLACK
           && i >= 0
           && j > 0)
    {
            m_board->m_board[i][j] = Board::TYPE_NEXT_STEP;

        --i;
        --j;
    }


    i = _i - 1;
    j = _j + 1;

    while( m_board->m_board[i][j] == Board::TYPE_BLACK
           && i >= 0
           && j < m_board->BOARD_WIDTH)
    {

            m_board->m_board[i][j] = Board::TYPE_NEXT_STEP;

        --i;
        ++j;
    }

    is_selected = true;
}


bool Controller::king_can_beat( int _i, int _j )
{
    Board::Cell enemy;
    Board::Cell enemyKing;

    if( white_moving )
    {
        enemy = Board::TYPE_BLACK_CHECKER;
        enemyKing = Board::TYPE_BLACK_KING;
    }
    else
     {
        enemy = Board::TYPE_WHITE_CHECKER;
        enemyKing = Board::TYPE_WHITE_KING;
    }


    /*----------------------------------------------------------------------*/
    int     i = _i + 1;
    int     j = _j - 1;
    bool    need_to_beat = false;
    is_selected = false;

    while( m_board->m_board[i][j] == Board::TYPE_BLACK
           && i < m_board->BOARD_HEIGHT
           && j >= 0 )
    {
        ++i;
        --j;
    }

    if(  m_board->m_board[i + 1][j - 1] == Board::TYPE_BLACK
         && ( m_board->m_board[i][j] == enemy || m_board->m_board[i][j] == enemyKing ) )
     {
        ++i;
        --j;

        is_selected = true;
        need_to_beat = true;
        while( m_board->m_board[i][j] == Board::TYPE_BLACK
               && i < m_board->BOARD_HEIGHT
               && j >= 0  )
          {

            m_board->m_board[i][j] = Board::TYPE_BEAT;
            ++i;
            --j;
        }

     }


    /*-----------------------------------------------------------------------*/
    i = _i + 1;
    j = _j + 1;

        while( m_board->m_board[i][j] == Board::TYPE_BLACK
               && i < m_board->BOARD_HEIGHT
               && j >= 0 )
        {
            ++i;
            ++j;
        }


        if(  m_board->m_board[i + 1][j + 1] == Board::TYPE_BLACK
             && ( m_board->m_board[i][j] == enemy || m_board->m_board[i][j] == enemyKing ) )
         {
            ++i;
            ++j;


            is_selected = true;
            need_to_beat = true;
            while( m_board->m_board[i][j] == Board::TYPE_BLACK
                   && i < m_board->BOARD_HEIGHT
                   && j >= 0  )
              {

                m_board->m_board[i][j] = Board::TYPE_BEAT;
                ++i;
                ++j;
            }

         }


    /*-----------------------------------------------------------------------*/
     i = _i - 1;
     j = _j - 1;

     while( m_board->m_board[i][j] == Board::TYPE_BLACK
                   && i < m_board->BOARD_HEIGHT
                   && j >= 0 )
            {
                --i;
                --j;
            }

            if(  m_board->m_board[i - 1][j - 1] == Board::TYPE_BLACK
                 && ( m_board->m_board[i][j] == enemy || m_board->m_board[i][j] == enemyKing ) )
             {
                --i;
                --j;


                is_selected = true;
                need_to_beat = true;
                while( m_board->m_board[i][j] == Board::TYPE_BLACK
                       && i < m_board->BOARD_HEIGHT
                       && j >= 0  )
                  {

                    m_board->m_board[i][j] = Board::TYPE_BEAT;
                    --i;
                    --j;
                }

             }
     /*-----------------------------------------------------------------------*/
            i = _i - 1;
            j = _j + 1;

            while( m_board->m_board[i][j] == Board::TYPE_BLACK
                          && i < m_board->BOARD_HEIGHT
                          && j >= 0 )
                   {
                       --i;
                       ++j;
                   }

                   if(  m_board->m_board[i - 1][j + 1] == Board::TYPE_BLACK
                        && ( m_board->m_board[i][j] == enemy || m_board->m_board[i][j] == enemyKing ) )
                    {
                       --i;
                       ++j;


                       is_selected = true;
                       need_to_beat = true;
                       while( m_board->m_board[i][j] == Board::TYPE_BLACK
                              && i < m_board->BOARD_HEIGHT
                              && j >= 0  )
                         {

                           m_board->m_board[i][j] = Board::TYPE_BEAT;
                           --i;
                           ++j;
                       }

                    }


   return need_to_beat;
}


void Controller::king_was_selected( int _i, int _j )
{
    unselect();
    if( ( white_moving && m_board->m_board[_i][_j] == Board::TYPE_WHITE_KING )
            || ( white_moving == false && m_board->m_board[_i][_j] == Board::TYPE_BLACK_KING ) )
     {
        if ( king_can_beat( _i, _j ) == false )
            setAllNewStepsByAllDirections( _i, _j );
     }

}


void Controller::king_beated( int _i, int _j )
{
    unselect();

    //если ходим белыми
   if( white_moving )
   {

      //меняем местами состояния
      m_board->m_board[_i][_j] = Board::TYPE_WHITE_KING;
      m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;


      removeTheBattered(_i,_j);
      m_currI = _i;
      m_currJ = _j;
   }
   else
   {
       m_board->m_board[_i][_j] = Board::TYPE_BLACK_KING;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;

       removeTheBattered(_i,_j);
       m_currI = _i;
       m_currJ = _j;
   }



   if( king_can_beat( m_currI, m_currJ ) == false )
    {
       white_moving = !white_moving;  //даем ход противнику
       is_selected = false;
    }
}


void Controller::if_moving( int _i, int _j )
{
    if( m_board->m_board[_i][_j] == Board::TYPE_NEXT_STEP )
       {
         if ( check_board_for_battle() == false )
         {
             if ( m_board->m_board[m_currI][m_currJ] == Board::TYPE_BLACK_KING
                  || m_board->m_board[m_currI][m_currJ] == Board::TYPE_WHITE_KING )
                 move_king( _i, _j );
             else
                 move_checker(_i, _j);
         }
         else
         {
             unselect();
             QMessageBox msg( "Ход невозможен"
                              , "Вы обязаны ударить вражескую шашку."
                              , QMessageBox::Critical
                              , QMessageBox::Ok
                              , 0
                              , 0
                              );
             msg.exec();
         }
       }
}


void Controller::selected(int _i, int _j)
{

    if ( m_board->m_board[_i][_j] == Board::TYPE_BLACK_KING
         || m_board->m_board[_i][_j] == Board::TYPE_WHITE_KING )
        king_was_selected(_i, _j);
    else
        checker_selected( _i, _j );

   //если мы ходим
    if_moving( _i, _j );

   //если бьем
    if ( m_board->m_board[_i][_j] == Board::TYPE_BEAT )
      {
        if( m_board->m_board[m_currI][m_currJ] == Board::TYPE_BLACK_CHECKER
                || m_board->m_board[m_currI][m_currJ] == Board::TYPE_WHITE_CHECKER )
            beat( _i, _j );
        else
            king_beated( _i, _j);
      }

        m_currI = _i;   //запоминаем координаты, что бы потом осуществить ход
        m_currJ = _j;

    //что бы не висели не нужные выделения
    if( is_selected == false )
      unselect();

    //перересуем доску
      emit m_board->repaint();

    check_for_win();
}


void Controller::check_for_win()
{
    if( m_whiteCount == 0 )
        emit black_player_won();
    else if ( m_blackCount == 0 )
        emit white_player_won();
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


void Controller::checkerToMove(int _i, int _j)
{
    unselect();          //убираем все выделения

    bool is_beat = false;

    if( white_moving )
       is_beat = whiteToBeat( _i + 1, _j );
    else
       is_beat = blackToBeat( _i - 1, _j );

    if( is_beat == false )
      {
        //проверяем пустые ли клеточки, для хода
        if( m_board->m_board[ _i ][ _j - 1 ] == Board::TYPE_BLACK )
          {
            m_board->m_board[ _i ][ _j - 1 ] = Board::TYPE_NEXT_STEP;
          }

        if( m_board->m_board[ _i ][ _j + 1 ] == Board::TYPE_BLACK )
          {
            m_board->m_board[ _i ][ _j + 1 ] = Board::TYPE_NEXT_STEP;
          }

    }

    is_selected = true;

}


void Controller::checker_selected( int _i, int _j )
{
            //если ходят белые, то
            if ( white_moving == true )
            {
                //если мы успешно выбрали белую шашку
                if ( m_board->m_board[_i][_j] == Board::TYPE_WHITE_CHECKER )
                    checkerToMove(_i - 1, _j); //выделяем все клеточки куда можно ходить
                else
                    is_selected = false;
            }
            else //если ходят черные
            {
                //если мы успешно выбрали черную шашку
                if ( m_board->m_board[_i][_j] == Board::TYPE_BLACK_CHECKER )
                   checkerToMove(_i + 1, _j); //выделяем все клеточки куда можно ходить
                else
                    is_selected = false; //если промахнулись, то убираем все выделения
            }

}


bool Controller::white_checker_beat( int _i, int _j, int _stepI, int _stepJ )
{
    if( ( m_board->m_board[ _i + _stepI ][ _j + _stepJ ] == Board::TYPE_BLACK_CHECKER || m_board->m_board[ _i + _stepI ][ _j + _stepJ ] == Board::TYPE_BLACK_KING )
                && m_board->m_board[ _i + _stepI * 2 ][ _j + _stepJ * 2 ] == Board::TYPE_BLACK )
        {
         m_board->m_board[ _i + _stepI * 2 ][ _j + _stepJ * 2 ] = Board::TYPE_BEAT;
         return true;
        }
    return false;
}


bool Controller::black_checker_beat( int _i, int _j, int _stepI, int _stepJ )
{
    if( ( m_board->m_board[ _i + _stepI ][ _j + _stepJ ] == Board::TYPE_WHITE_CHECKER || m_board->m_board[ _i + _stepI ][ _j + _stepJ ] == Board::TYPE_WHITE_KING )
                        && m_board->m_board[ _i + _stepI * 2 ][ _j + _stepJ * 2 ] == Board::TYPE_BLACK )
            {
               m_board->m_board[ _i + _stepI * 2 ][ _j + _stepJ * 2 ] = Board::TYPE_BEAT;
              return true;
            }
    return false;
}


bool Controller::whiteToBeat(int _i, int _j)
{

    bool need_to_beat = false; //если есть, что ударить. других ходов быть не может.

    //бить вперед

    if( white_checker_beat( _i, _j, -1, 1 ) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    if( white_checker_beat( _i, _j, -1, -1 ) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    if( white_checker_beat( _i, _j, 1, -1 ) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    if( white_checker_beat( _i, _j, 1, 1 ) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    return need_to_beat;
}


bool Controller::blackToBeat(int _i, int _j)
{
    bool need_to_beat = false; //если есть, что ударить. других ходов быть не может.

    //проверяем врагов спереди
    if ( black_checker_beat( _i, _j, 1, -1) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    if ( black_checker_beat( _i, _j, 1, 1) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    if ( black_checker_beat( _i, _j, -1, -1) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    if ( black_checker_beat( _i, _j, -1, 1) )
    {
        is_selected = true;
        need_to_beat = true;
    }

    return need_to_beat;
}


void Controller::move_king( int _i, int _j )
{
    if ( white_moving )
    {
        m_board->m_board[_i][_j] = Board::TYPE_WHITE_KING;
        m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
    }
    else
    {
        m_board->m_board[_i][_j] = Board::TYPE_BLACK_KING;
        m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
    }

    white_moving = !white_moving;
    is_selected = false;
}


void Controller::move_checker(int _i, int _j)
{
    //если ходим белыми
   if( white_moving )
   {
       if( _i == 0 )//если достигли конца - делаем дамку
       {
           m_board->m_board[_i][_j] = Board::TYPE_WHITE_KING;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
        else
       {
           //меняем местами состояния
           m_board->m_board[_i][_j] = Board::TYPE_WHITE_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }

   }
   else
   {
       //тоже самое для черных

       if( _i == m_board->BOARD_HEIGHT - 1 )
       {
           m_board->m_board[_i][_j] = Board::TYPE_BLACK_KING;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
       else
        {
           m_board->m_board[_i][_j] = Board::TYPE_BLACK_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
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
       if( _i == 0 )//если достигли конца - делаем дамку
       {
           m_board->m_board[_i][_j] = Board::TYPE_WHITE_KING;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
        else
       {
           //меняем местами состояния
           m_board->m_board[_i][_j] = Board::TYPE_WHITE_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }

       removeTheBattered(_i, _j);
       m_currI = _i;
       m_currJ = _j;
       whiteToBeat( _i, _j );
   }
   else
   {
       if( _i == m_board->BOARD_HEIGHT - 1 )
       {
           m_board->m_board[_i][_j] = Board::TYPE_BLACK_KING;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }
       else
        {
           //тоже самое для черных
           m_board->m_board[_i][_j] = Board::TYPE_BLACK_CHECKER;
           m_board->m_board[m_currI][m_currJ] = Board::TYPE_BLACK;
       }

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
    int tmpI = m_currI;
    int tmpJ = m_currJ;

    if( _j > m_currJ && _i < m_currI )
       {
        while( tmpI != _i && tmpJ != _j )
         {
            m_board->m_board[tmpI][ tmpJ ] = Board::TYPE_BLACK;
            tmpJ++;
            tmpI--;
         }
    }

    else if( _j < m_currJ && _i < m_currI )
    {
     while( tmpI != _i && tmpJ != _j )
      {
         m_board->m_board[tmpI][ tmpJ ] = Board::TYPE_BLACK;
         tmpJ--;
         tmpI--;
      }
    }

    else if( _j > m_currJ && _i > m_currI )
    {
     while( tmpI != _i && tmpJ != _j )
      {
         m_board->m_board[tmpI][ tmpJ ] = Board::TYPE_BLACK;
         tmpJ++;
         tmpI++;
      }
    }

    else if( _j < m_currJ && _i > m_currI )
    {
     while( tmpI != _i && tmpJ != _j )
      {
         m_board->m_board[tmpI][ tmpJ ] = Board::TYPE_BLACK;
         tmpJ--;
         tmpI++;
      }
    }

    if( white_moving )
        --m_blackCount;
    else
        --m_whiteCount;
}
