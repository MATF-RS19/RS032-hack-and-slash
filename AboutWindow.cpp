#include "AboutWindow.h"
#include "ui_AboutWindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    QPixmap background(":/Assets/UI/MainMenu.jpg");
    QPalette plt;
    plt.setBrush(QPalette::Background, background.scaled(this->size(), Qt::IgnoreAspectRatio));
    this->setPalette(plt);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
