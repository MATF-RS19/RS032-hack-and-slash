#include <QApplication>
#include "MainWindow.h"

#include "Engine.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.showWindow();

    return a.exec();
}
