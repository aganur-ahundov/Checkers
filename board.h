#ifndef CHECKER_H
#define CHECKER_H

#include <QWidget>
#include <memory>
#include "gamepainter.h"


class Controller;

class Board : public QWidget
{
    Q_OBJECT

    //предостовляем доступ к полю классу контроллеру
    //что бы было меньше вызовов геттеров и сеттеров
    friend Controller;
public:

    //все возможные клетки на доске
    enum Cell
    {
        TYPE_BLACK_CHECKER,
        TYPE_BLACK_KING,
        TYPE_WHITE_CHECKER,
        TYPE_WHITE_KING,
        TYPE_WHITE,
        TYPE_BLACK,
        TYPE_NEXT_STEP,
        TYPE_BEAT
    };

    //высота и длина шашек по-умолчанию
    static const short BOARD_HEIGHT = 8;
    static const short BOARD_WIDTH  = 8;

public:
    explicit Board( QWidget *parent = 0 );
    ~Board() = default;

signals:
    void clicked( int _i, int _j );  //сигналим о том, что мышь кликнула по виджету

public:
    //доступ к полям есть у класса контроллер, но вдруг пригодиться в других случаях
    Cell getType   ( int _x, int _j ) const;   //а вдруг пригодиться
    void changeType( int _x, int _j, Cell _t );//вряд ли, но все же

protected:
    //переопределяем события
    void mousePressEvent( QMouseEvent* _e );
    void paintEvent( QPaintEvent* _e );

private:
    Cell m_board[BOARD_WIDTH][BOARD_HEIGHT]; //матрица - поле
    GamePainter m_painter;                   //класс прорисует приложение
};

#endif // CHECKER_H
