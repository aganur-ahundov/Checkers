#ifndef CHECKER_H
#define CHECKER_H

#include <QWidget>
#include <memory>
#include "gamepainter.h"


class Controller;

class Board : public QWidget
{
    Q_OBJECT

    friend Controller;
public:

    enum Cell
    {
        TYPE_BLACK_CHECKER,
        TYPE_BLACK_KING,
        TYPE_WHITE_CHECKER,
        TYPE_WHITE_KING,
        TYPE_WHITE,
        TYPE_BLACK,
        TYPE_NEXT_STEP
    };


    static const short BOARD_HEIGHT = 8;
    static const short BOARD_WIDTH  = 8;

public:
    explicit Board( QWidget *parent = 0 );
    ~Board() = default;

signals:
    void type_was_changed();
    void clicked( int _i, int _j );

public slots:
//    void cell_was_selected();

public:
    Cell getType   ( int _x, int _j ) const;
    void changeType( int _x, int _j, Cell _t );

protected:
    void mousePressEvent( QMouseEvent* _e );
    void paintEvent( QPaintEvent* _e );

private:
    Cell m_board[BOARD_WIDTH][BOARD_HEIGHT];
    GamePainter m_painter;
};

#endif // CHECKER_H
