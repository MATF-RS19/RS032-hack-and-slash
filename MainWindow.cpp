#include "ChooseWindow.h"
#include "ui_ChooseWindow.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AboutWindow.h"
#include "ui_AboutWindow.h"

#include <QtMultimedia/QMediaPlayer>

#include "Engine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap background(":/Assets/UI/MainMenu.jpg");
    QPalette plt;
    plt.setBrush(QPalette::Background, background.scaled(this->size(), Qt::IgnoreAspectRatio));
    this->setPalette(plt);

    QPixmap pixmap(":/Assets/UI/button.png");
    QPalette palette;
    QPalette palette1;
    QPalette palette2;
    palette.setBrush(ui->playButton->backgroundRole(), QBrush(pixmap.scaled(ui->playButton->maximumWidth(), ui->playButton->maximumHeight(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    palette1.setBrush(ui->aboutButton->backgroundRole(), QBrush(pixmap.scaled(ui->playButton->maximumWidth(), ui->playButton->maximumHeight(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    palette2.setBrush(ui->exitButton->backgroundRole(), QBrush(pixmap.scaled(ui->playButton->maximumWidth(), ui->playButton->maximumHeight(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->playButton->setFlat(true);
    ui->playButton->setAutoFillBackground(true);
    ui->playButton->setPalette(palette);

    ui->aboutButton->setFlat(true);
    ui->aboutButton->setAutoFillBackground(true);
    ui->aboutButton->setPalette(palette1);

    ui->exitButton->setFlat(true);
    ui->exitButton->setAutoFillBackground(true);
    ui->exitButton->setPalette(palette2);

    ui->label->setText("<font color = 'white'>Hack & Slash</font>");


    Engine::getInstance().setMainWindow(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showWindow(){
    Engine::getInstance().playSound("./Assets/Sounds/MenuTheme.mp3", 20);
    show();
}


void MainWindow::on_playButton_clicked(){
    Engine::getInstance().playSound("./Assets/Sounds/Click.wav");

    ChooseWindow* w = new  ChooseWindow();
    w->show();

    hide();
}

void MainWindow::on_exitButton_clicked(){
    Engine::getInstance().playSound("./Assets/Sounds/Click.wav");

    QApplication::quit();
}


void MainWindow::on_aboutButton_clicked(){
    Engine::getInstance().playSound("./Assets/Sounds/Click.wav");

    AboutWindow* w = new  AboutWindow();
    w->show();

    hide();
}
