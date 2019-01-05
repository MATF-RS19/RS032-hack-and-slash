#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include <tuple>

#include "Map.h"
#include "Camera.h"
#include "Animator.h"
#include "Character.h"
#include "Player.h"

struct CharTemplate;

class Engine : public QObject {
    Q_OBJECT
public:
    static Engine& getInstance();
    void run();
    QPixmap getAssetTiles(int i);
    Animator getAssetEnv(int i);
    CharTemplate getTemplate(int i);
    Animator getAssetAnim(int i);

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
    QVector<CharTemplate> charTemplates;
    QVector<QPixmap> assetsTiles;
    QVector<Animator> assetsAnims;
    QVector<Animator> assetsEnv;
};

struct CharTemplate{
    CharTemplate() {}
    CharTemplate(int animIndex, int size, int health, float speed, int aggroRange = 0, int deaggroRange = 0){
        this->animIndex = animIndex;
        this->size = size;
        this->health = health;
        this->speed = speed;
        this->aggroRange = aggroRange;
        this->deaggroRange = deaggroRange;
    }

    int animIndex = 0;
    int size = 0;
    int health = 0;
    float speed = 0;
    int aggroRange = 0;
    int deaggroRange = 0;
};

#endif // ENGINE_H
