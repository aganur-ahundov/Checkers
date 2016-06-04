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
    void start_game();

public slots:
    void selected ( int _i, int _j );
    void show();

private:
    void unselect();

    void whiteToMove( int _i, int _j );
    void blackToMove( int _i, int _j );

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
