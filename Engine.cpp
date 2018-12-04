#include "Engine.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

#include "Map.h"
#include "Character.h"

void Engine::run() {
    m = new Map();

    cam = new Camera(m);
    cam->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->show();
    cam->setFixedSize(300, 300);
    m->setSceneRect(0,0,300,300);

    ch = new Player(m, 0, 0, 100, 100);

    m->setPlayer(ch);
    m->addItem(ch);

    QVector2D pos = m->mapToScene(m->matrixToMap(ch->getI(), ch->getJ()));

    ch->setPos(pos.x(), pos.y());

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void Engine::update() {
    ch->update(10);
    //scene->update();
}
