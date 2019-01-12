#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QtMultimedia/QMediaPlayer>

#include <tuple>

#include "Map.h"
#include "Camera.h"
#include "Animator.h"
#include "Character.h"
#include "MainWindow.h"
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
    Animator getAssetSpell(int i);
    Spell* getSpell(int i);
    Map* getMap();
    void setMainWindow(MainWindow* w);
    Camera* getCam();
    void endGame();
    void playSound(QString path, int volume = 50);
    void stopSound();

    Engine(Engine const&) = delete;
    void operator = (Engine const&) = delete;

public slots:
    void update();
private:
    Engine(){}

    MainWindow* w;

    Map* m = nullptr;
    Camera* cam = nullptr;

    QTimer* timer = nullptr;

    QVector<CharTemplate> charTemplates;
    QVector<QPixmap> assetsTiles;
    QVector<Animator> assetsAnims;
    QVector<Animator> assetsEnv;
    QVector<Animator> assetsSpells;

    QMediaPlayer* sound;
};

struct CharTemplate{
    CharTemplate() {}
    CharTemplate(int animIndex, int size, int health, float speed, int aggroRange, int deaggroRange, QVector<int> spells){
        this->animIndex = animIndex;
        this->size = size;
        this->health = health;
        this->speed = speed;
        this->aggroRange = aggroRange;
        this->deaggroRange = deaggroRange;
        this->spells = spells;
    }

    int animIndex = 0;
    int size = 0;
    int health = 0;
    float speed = 0;
    int aggroRange = 0;
    int deaggroRange = 0;
    QVector<int> spells = QVector<int>();

};

struct SpellInfo{
    SpellInfo() {}
    SpellInfo(QString name, int width, int height, int scaleWidth, int begin, int end){
        this->name = name;
        this->width = width;
        this->height = height;
        this->scaleWidth = scaleWidth;
        this->begin = begin;
        this->end = end;
    }

    QString name;
    int width;
    int height;
    int scaleWidth;
    int begin;
    int end;
};

#endif // ENGINE_H
