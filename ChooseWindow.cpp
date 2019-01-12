#include "ChooseWindow.h"
#include "ui_ChooseWindow.h"

#include "LoadingScreen.h"
#include "ui_LoadingScreen.h"

#include "Engine.h"

#include <QDebug>

ChooseWindow::ChooseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseWindow)
{
    Engine::getInstance().playSound("./Assets/Sounds/MenuTheme.mp3", 20);
    ui->setupUi(this);

    QPixmap background(":/Assets/UI/MainMenu.jpg");
    QPalette plt;
    plt.setBrush(QPalette::Background, background.scaled(this->size(), Qt::IgnoreAspectRatio));
    this->setPalette(plt);

    QPixmap pixmapHack(":/Assets/UI/Hack.png");
    QPalette paletteHack;
    paletteHack.setBrush(ui->hackButton->backgroundRole(), QBrush(pixmapHack.scaled(ui->hackButton->width(), ui->hackButton->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    ui->hackButton->setFlat(true);
    ui->hackButton->setAutoFillBackground(true);
    ui->hackButton->setPalette(paletteHack);

    QPixmap pixmapSlash(":/Assets/UI/Slash.png");
    QPalette paletteSlash;
    paletteSlash.setBrush(ui->slashButton->backgroundRole(), QBrush(pixmapSlash.scaled(ui->hackButton->width(), ui->slashButton->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    ui->slashButton->setFlat(true);
    ui->slashButton->setAutoFillBackground(true);
    ui->slashButton->setPalette(paletteSlash);
}

ChooseWindow::~ChooseWindow(){
    delete ui;
}

void ChooseWindow::on_hackButton_clicked(){
    Engine::getInstance().playSound("./Assets/Sounds/Click.wav");

    LoadingScreen* screen = new LoadingScreen();
    screen->setPlayer(0);
    screen->show();

    close();
}

void ChooseWindow::on_slashButton_clicked()
{
    Engine::getInstance().playSound("./Assets/Sounds/Click.wav");

    LoadingScreen* screen = new LoadingScreen();
    screen->setPlayer(1);
    screen->show();

    close();
}
