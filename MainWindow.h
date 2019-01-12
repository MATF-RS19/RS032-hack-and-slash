#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showWindow();

private slots:
    void on_playButton_clicked();

    void on_aboutButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
