#include "Engine.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QTransform>
#include <QDebug>

#include "Map.h"
#include "Character.h"
#include "Animator.h"

void Engine::run() {
    assetsTiles = {QPixmap(":/Assets/Sivakocka.png")};
    assetsTiles[0] = assetsTiles[0].scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QTransform transform;
    transform.scale(1.04, 0.52);
    transform.rotate(-45);

    assetsTiles[0] = assetsTiles[0].transformed(transform);

    assetsAnims = {Animator(QPixmap(":/Assets/CharacterAsset8x58.png").scaled(5800*1.8,800*1.8, Qt::KeepAspectRatio,Qt::SmoothTransformation), 58, 8)};
    for(int i = 0; i < 8; i++) {
        assetsAnims[0].addAnimation(58 * i + 27, 58 * i + 39, 60, true);
        assetsAnims[0].addAnimation(58 * i + 0, 58 * i + 15, 60, true);
    }

    m = new Map();

    cam = new Camera(m, 20, 20);

    cam->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->show();
    cam->setFixedSize(1920, 1080);
    m->setSceneRect(-1920/2, -1080/2, 1920, 1080);

    ch = new Player(m, 1, 1, 50 * 1.8, 60 * 1.8, assetsAnims[0]);

    m->setPlayer(ch);
    m->addItem(ch);

    ch->setCam(cam);

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

Engine& Engine::getInstance(){
    static Engine instance;
    return instance;
}

QPixmap Engine::getAssetTiles(int i){
    return assetsTiles[i];
}

void Engine::update() {
    ch->update(10);
    //scene->update();
}
