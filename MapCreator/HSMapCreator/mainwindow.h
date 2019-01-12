#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "animator.h"
class Map;
#include "mapitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap getPixmap(MapItem::Type t, int i);
    int getMode();
    int getAssetIdx();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_3_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    Map* m;

    QVector<QString> namesTiles;
    QVector<QPixmap> assetsTiles;

    QVector<QString> namesAnims;
    QVector<Animator> assetsAnims;

    QVector<int> assetsChars;
    QVector<QString> namesEnv;
    QVector<Animator> assetsEnv;
};

#endif // MAINWINDOW_H
