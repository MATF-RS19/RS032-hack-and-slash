#include <QApplication>

#include "Engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Engine* engine = new Engine();
    engine->run();

    return a.exec();
}
