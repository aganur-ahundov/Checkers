#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
class Board;

class Controller : public QWidget
{
    Q_OBJECT

public:
    Controller( QWidget* _parent = 0 );
    ~Controller();

public:
    void start_game();  //старт

public slots:
    void selected ( int _i, int _j ); //обрабатываем нажатие мыши
    void show();                       //переопределяем функцию

private:
    void unselect();          //убираем все выделения

    void whiteToMove        ( int _i, int _j ); //ходят белые
    void blackToMove        ( int _i, int _j ); //ходят черные
    bool whiteToBeat        ( int _i, int _j ); //выделяем ячейки что бы бить
    bool blackToBeat        ( int _i, int _j );
    void move_checker       ( int _i, int _j ); //вспомогательная функция. осущ-т ход
    void beat               ( int _i, int _j ); //даем возможность ударить
    void removeTheBattered  ( int _i, int _j ); //убираем битую шашку


private:
    Board* m_board;     //игровая доска

    int m_blackCount;
    int m_whiteCount;    //кол-во шашек у каждого игрока

    int m_currI;
    int m_currJ;         // текущая выделенная клетка

    bool white_moving;   //чей черед ходить. 1 - белые, 2 - черные
    bool is_selected;
};

#endif // CONTROLLER_H
