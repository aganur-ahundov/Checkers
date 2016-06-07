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
    void if_moving( int _i, int _j );

private:
    void unselect();                            //убираем все выделения
    void checkerToMove      ( int _i, int _j ); //ход шашки
    void checker_selected   ( int _i, int _j ); //реакция программы на выделение шашки
    bool whiteToBeat        ( int _i, int _j ); //выделяем ячейки что бы бить
    bool blackToBeat        ( int _i, int _j );
    void move_checker       ( int _i, int _j ); //вспомогательная функция. осущ-т ход
    void beat               ( int _i, int _j ); //даем возможность ударить
    void removeTheBattered  ( int _i, int _j ); //убираем битую шашку
    bool black_checker_beat ( int _i, int _j, int _stepI, int _stepJ ); //вспомогательная функция, для определения направления боя
    bool white_checker_beat ( int _i, int _j, int _stepI, int _stepJ ); //-,-,-
    bool check_board_for_battle();  //проверяем, есть ли возможность ударить, перед ходом

private: //все необходимые функции для реализации дамки
    void king_was_selected              ( int _i, int _j ); //дамка выбрана - поехали
    void setAllNewStepsByAllDirections  ( int _i, int _j ); //отмечает все клетки, куда может ходить дамка
    void move_king                      ( int _i, int _j ); //ходим дамкой



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
