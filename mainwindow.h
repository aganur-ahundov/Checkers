#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void white_won();
    void black_won();
    void pause();
    void restart_game();

private:
    void createWhiteWonMenu();
    void createBlackWonMenu();
    void createMenuPause();


private:
    Ui::MainWindow *ui;

    Controller      m_game;
    QWidget         m_whiteWon;
    QWidget         m_blackWon;
    QWidget         m_pauseMenu;
};

#endif // MAINWINDOW_H
