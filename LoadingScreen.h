#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QMainWindow>

namespace Ui {
class LoadingScreen;
}

class LoadingScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingScreen(QWidget *parent = nullptr);
    ~LoadingScreen();

    void setPlayer(int p);
private slots:
    void load();

private:
    Ui::LoadingScreen *ui;

    int player;
};

#endif // LOADINGSCREEN_H
