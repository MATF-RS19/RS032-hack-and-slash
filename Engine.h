#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include "Map.h"
#include "Character.h"
#include "Player.h"
#include "Camera.h"
#include "Animator.h"

class Engine : public QObject {
    Q_OBJECT
public:
    static Engine& getInstance();
    void run();
    QPixmap getAssetTiles(int i);

    Engine(Engine const&) = delete;
    void operator = (Engine const&) = delete;

public slots:
    void update();
private:
    //QGraphicsView* view;
    Engine(){}

    Map* m;
    Player* ch;
    Camera* cam;
    QVector<QPixmap> assetsTiles;
    QVector<Animator> assetsAnims;
};

#endif // ENGINE_H
