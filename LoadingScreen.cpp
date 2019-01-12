#include "LoadingScreen.h"
#include "ui_LoadingScreen.h"

#include <QMovie>
#include <QLabel>
#include <QTimer>

#include "Engine.h"

LoadingScreen::LoadingScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingScreen)
{
    ui->setupUi(this);

    QMovie* movie = new QMovie(":/Assets/UI/LoadingScreen.gif");
    movie->setScaledSize(ui->label->maximumSize());
    ui->label->setMovie(movie);
    movie->start();

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(load()));
    timer->setSingleShot(true);
    timer->start(3000);
}

LoadingScreen::~LoadingScreen()
{
    delete ui;
}

void LoadingScreen::load() {
    Engine::getInstance().run();
    close();
}
