#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Map.h"
#include "Character.h"
#include "Player.h"
#include "Camera.h"

class Engine : public QObject {
    Q_OBJECT
public:
    void run();
public slots:
    void update();
private:
    QGraphicsView* view;

    Map* m;
    Player* ch;
    Camera* cam;
};

#endif // ENGINE_H
