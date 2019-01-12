#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChooseWindow;
}

class ChooseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseWindow(QWidget *parent = nullptr);
    ~ChooseWindow();

private slots:
    void on_hackButton_clicked();


private:
    Ui::ChooseWindow *ui;
};

#endif // CHOOSEWINDOW_H
