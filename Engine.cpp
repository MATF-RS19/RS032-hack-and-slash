#include "Engine.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QTransform>
#include <QDebug>
#include <QFile>

#include "Map.h"
#include "Character.h"
#include "Animator.h"
#include "Spell.h"

void Engine::run() {

    QFile fileTiles(":/Assets/tiles.hsa");
    fileTiles.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileTiles.atEnd()){
        QString line = fileTiles.readLine();
        assetsTiles.push_back(QPixmap(line.trimmed()));
    }

    fileTiles.close();

    QTransform transform;
    transform.scale(1.04, 0.52);
    transform.rotate(-45);

    for(int i = 0; i < assetsTiles.size(); i++){
        assetsTiles[i] = assetsTiles[i].scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        assetsTiles[i] = assetsTiles[i].transformed(transform);
    }

    QFile fileAnim(":/Assets/anim.hsa");
    fileAnim.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileAnim.atEnd()){
        QString line = fileAnim.readLine();
        QStringList args = line.split(" ");
        QString name = args[0];
        int dimX = args[1].toInt();
        int dimY = args[2].toInt();
        int frameWidth = args[3].toInt();
        int frameHeight = args[4].toInt();
        int offsetX = args[5].toInt();
        int offsetY = args[6].toInt();
        int animCount = args[7].toInt();
        int distinctCount = args[8].toInt();

        assetsAnims.push_back(Animator(QPixmap(name).scaled(frameWidth * dimX, frameHeight * dimY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), dimX, dimY, offsetX, offsetY));
        for(int i = 0; i < distinctCount; i++){
            line = fileAnim.readLine();
            args = line.split(" ");
            int begin = args[0].toInt();
            int end = args[1].toInt();
            int duration = args[2].toInt();
            bool looping = args[3].toInt();

            for(int j = 0; j < animCount/distinctCount; j++)
                assetsAnims[assetsAnims.size()-1].addAnimation(dimX * j + begin, dimX * j + end, duration, looping);
        }
    }

    fileAnim.close();

    QFile fileEnv(":/Assets/env.hsa");
    fileEnv.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileEnv.atEnd()){
        QString line = fileEnv.readLine().trimmed();
        QStringList args = line.split(" ");
        QString name = args[0];
        int dimX = args[1].toInt();
        int dimY = args[2].toInt();
        int width = args[3].toInt();
        int begin = args[4].toInt();
        int end = args[5].toInt();
        int duration = args[6].toInt();
        if(args.size() == 7)
            assetsEnv.push_back(Animator(QPixmap(name).scaledToWidth(width * dimX, Qt::SmoothTransformation), dimX, dimY));
        if(args.size() == 9){
            int offsetX = args[7].toInt();
            int offsetY = args[8].toInt();
            assetsEnv.push_back(Animator(QPixmap(name).scaledToWidth(width * dimX, Qt::SmoothTransformation), dimX, dimY, offsetX, offsetY));
        }
        assetsEnv[assetsEnv.size() - 1].addAnimation(begin, end, duration, true);
    }

    fileEnv.close();

    QFile fileChar(":/Assets/chars.hsa");
    fileChar.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileChar.atEnd()){
        QString line = fileChar.readLine().trimmed();
        QStringList args = line.split(" ");
        int animIndex = args[0].toInt();
        int size = args[1].toInt();
        int health = args[2].toInt();
        float speed = args[3].toFloat();
        int aggroRange = args[4].toInt();
        int deaggroRange = args[5].toInt();
        QVector<int> spells;
        for(int i = 6; i < args.size(); i++)
            spells.push_back(args[i].toInt());
        charTemplates.push_back(CharTemplate(animIndex, size, health, speed, aggroRange, deaggroRange, spells));
    }

    QFile fileSpells(":/Assets/spells.hsa");
    fileSpells.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!fileSpells.atEnd()){
        QString line = fileSpells.readLine().trimmed();
        QStringList args = line.split(" ");
        QString name = args[0];
        int dimX = args[1].toInt();
        int dimY = args[2].toInt();
        int width = args[3].toInt();
        int begin = args[4].toInt();
        int end = args[5].toInt();
        int duration = args[6].toInt();
        if(args.size() == 7)
            assetsSpells.push_back(Animator(QPixmap(name).scaledToWidth(width * dimX, Qt::SmoothTransformation), dimX, dimY));
        if(args.size() == 9){
            int offsetX = args[7].toInt();
            int offsetY = args[8].toInt();
            assetsSpells.push_back(Animator(QPixmap(name).scaledToWidth(width * dimX, Qt::SmoothTransformation), dimX, dimY, offsetX, offsetY));
        }
        assetsSpells[assetsSpells.size() - 1].addAnimation(begin, end, duration, true);
    }

    m = new Map(":Levels/test.hsl");

    cam = new Camera(m, 20, 20);

    cam->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->show();
    cam->setFixedSize(1280, 1024);
    m->setSceneRect(-1280/2, -1024/2, 1280, 1024);

    //ch = new Player(m, 1, 1, 1, assetsAnims[0]);

    //m->setPlayer(ch);
    //m->addItem(ch);

    m->setCam(cam);

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

Animator Engine::getAssetEnv(int i){
    return assetsEnv[i];
}

void Engine::update() {
    m->update(10);

    //scene->update();
}

CharTemplate Engine::getTemplate(int i){
    return charTemplates[i];
}

Animator Engine::getAssetAnim(int i){
    return assetsAnims[i];
}

Animator Engine::getAssetSpell(int i){
    return assetsSpells[i];
}

Spell* Engine::getSpell(int i){
    switch(i) {
    case 1:
        return new FirestormSpell();
    case 2:
        return new FlamethrowerSpell();
    case 3:
        return new SlowSpell();
    case 4:
        return new FireballSpell();
    case 5:
        return new HealSpell();
    case 6:
        return new DarkbeadSpell();
    case 7:
        return new DarkfogSpell();
    case 8:
        return new SilenceSpell();
    case 9:
        return new DarkorbsSpell();
    }
}
