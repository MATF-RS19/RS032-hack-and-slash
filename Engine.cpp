#include "Engine.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QTransform>
#include <QFile>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>

#include "Map.h"
#include "Character.h"
#include "Animator.h"
#include "Spell.h"
#include "UIController.h"

void Engine::run(int player) {
    stopSound();

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
        int mana = args[3].toInt();
        float attackRange = args[4].toFloat();
        int attackCooldown = args[5].toInt();
        int attackDmg = args[6].toInt();
        float speed = args[7].toFloat();
        int aggroRange = args[8].toInt();
        int deaggroRange = args[9].toInt();
        QVector<int> spells;
        for(int i = 10; i < args.size(); i++)
            spells.push_back(args[i].toInt());
        charTemplates.push_back(CharTemplate(animIndex, size, health, mana, attackRange, attackCooldown, attackDmg, speed, aggroRange, deaggroRange, spells));
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

    fileSpells.close();

    if(!m)
        m = new Map(":/Levels/level1.hsl", player);
    else
        m->loadMap(":/Levels/level1.hsl", player);

    if(!cam)
        cam = new Camera(m, 300, 300);
    else
        cam->setScene(m);

    cam->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cam->showFullScreen();
    cam->setBackgroundBrush(Qt::black);
    m->setSceneRect(-cam->width(), -cam->height(), 2*cam->width(), 2*cam->height());

    UIController::getInstance().load();

    if(!timer) {
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    }
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
    UIController::getInstance().update(10);
    //scene->update();
}

CharTemplate Engine::getTemplate(int i){
    return charTemplates[i];
}

Animator Engine::getAssetAnim(int i){
    return assetsAnims[i];
}

Map* Engine::getMap(){
    return m;
}

Animator Engine::getAssetSpell(int i){
    return assetsSpells[i];
}

void Engine::playSound(QString path, int volume){
    if(!sound)
        sound = new QMediaPlayer();

    sound->setMedia(QUrl(path));
    sound->setVolume(volume);
    sound->play();
}

void Engine::stopSound(){
    sound->stop();
}

void Engine::setMainWindow(MainWindow* w){
    this->w = w;
}

void Engine::endGame(){
    timer->stop();

    UIController::getInstance().reset();

    cam->setScene(nullptr);
    cam->hide();
    //m->clear();
    m->clearMap();
    //m = nullptr;
    //delete m;

    //delete m;
    //delete cam;


    charTemplates.clear();
    assetsTiles.clear();
    assetsAnims.clear();
    assetsEnv.clear();
    assetsSpells.clear();

    w->showWindow();
}

Camera* Engine::getCam(){
    return cam;
}

Spell* Engine::getSpell(int i){
    switch(i) {
    case 0:
        return new ShieldSpell();
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
