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
private slots:
    void load();

private:
    Ui::LoadingScreen *ui;
};

#endif // LOADINGSCREEN_H
