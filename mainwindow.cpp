#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bg("../Checkers_v2/resources/main_background.jpg");
    bg = bg.scaled( this->size() );

    QPalette p;
    p.setBrush( this->backgroundRole(), QBrush( bg ) );
    this->setPalette( p );

    createWhiteWonMenu();
    createBlackWonMenu();
    createMenuPause();

    connect( &m_game, SIGNAL(black_player_won()), SLOT(black_won()) );
    connect( &m_game, SIGNAL(white_player_won()), SLOT(white_won()) );
    connect( &m_game, SIGNAL(menu()), SLOT(pause()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    m_game.close();
    m_whiteWon.close();
    m_blackWon.close();
    m_pauseMenu.close();
}


void MainWindow::on_pushButton_clicked()
{
    this->hide();
    m_game.show();
}


void MainWindow::createBlackWonMenu()
{
    m_blackWon.resize( this->size() );

    QPushButton* restart = new QPushButton( "Restart", &m_blackWon );
    restart->resize( 150, 70 );
    restart->move( m_blackWon.width()/2 - 70, 250 );
    restart->setDefault( true );

    connect( restart, SIGNAL( clicked() ), SLOT(restart_game()) );

    QPushButton* exit = new QPushButton( "Exit", &m_blackWon );
    exit->resize( 150, 70 );
    exit->move( m_blackWon.width()/2 - 70, 370 );


    connect( exit, SIGNAL( clicked() ), SLOT(on_pushButton_2_clicked()) );

    QPixmap pm( "../Checkers_v2/resources/darkness_won.png" );
    pm = pm.scaled( m_blackWon.size().width(), m_blackWon.size().height() + 50 );

    QPalette pal;
    pal.setBrush( m_blackWon.backgroundRole(), QBrush( pm ) );
    m_blackWon.setPalette( pal );
}

void MainWindow::createWhiteWonMenu()
{
    m_whiteWon.setFixedSize( this->size() );

    QPixmap pm( "../Checkers_v2/resources/light_won.png" );
    pm = pm.scaled( m_whiteWon.size().width() + 340, m_whiteWon.size().height() );

    QPalette pal;
    pal.setBrush( m_whiteWon.backgroundRole(), QBrush( pm ) );
    m_whiteWon.setPalette( pal );



    QPushButton* restart = new QPushButton( "Restart", &m_whiteWon );
    restart->resize( 150, 70 );
    restart->move( m_whiteWon.width()/2 - 65, 250 );
    restart->setDefault( true );

    connect( restart, SIGNAL( clicked() ), SLOT(restart_game()) );

    QPushButton* exit = new QPushButton("Exit", &m_whiteWon );
    exit->resize( 150, 70 );
    exit->move( m_whiteWon.width()/2 - 65, 370 );

    connect( exit, SIGNAL( clicked() ), SLOT(on_pushButton_2_clicked()) );


}

void MainWindow::white_won()
{
    m_game.hide();
    m_whiteWon.show();
}

void MainWindow::createMenuPause()
{
    m_pauseMenu.resize( this->size() );

    QPixmap pm( "../Checkers_v2/resources/pause.jpg" );
    pm = pm.scaled( m_pauseMenu.size() );

    QPalette pal;
    pal.setBrush( m_pauseMenu.backgroundRole(), QBrush( pm ) );
    m_pauseMenu.setPalette( pal );


    QPushButton* restart = new QPushButton( "Restart", &m_pauseMenu );
    restart->resize( 100, 100 );
    restart->move( m_whiteWon.width()/2 - 65, 250 );
    restart->setDefault( true );

    connect( restart, SIGNAL( clicked() ), SLOT(restart_game()) );

    QPushButton* exit = new QPushButton( "Exit", &m_pauseMenu );
    exit->resize( 100, 100 );
    exit->move( m_whiteWon.width()/2 - 65, 370 );

    connect( exit, SIGNAL( clicked() ), SLOT(on_pushButton_2_clicked()) );


}

void MainWindow::black_won()
{
    m_game.hide();
    m_blackWon.show();
}


void MainWindow::restart_game()
{
    m_pauseMenu.hide();
    m_whiteWon.hide();
    m_blackWon.hide();

    m_game.restart();
}


void MainWindow::pause()
{
    m_game.hide();
    m_pauseMenu.show();
}
