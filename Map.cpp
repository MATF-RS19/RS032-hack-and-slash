#include "Map.h"

#include <QQueue>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QDebug>

#include <cmath>

#include "Engine.h"
#include "Character.h"
#include "Player.h"
#include "AnimatedItem.h"
#include "Enemy.h"

Map::Map(QString levelName){
    QFile file(levelName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString line = file.readLine();
    QStringList list = line.split(" ");
    int n = list.at(0).toInt();
    int m = list.at(1).toInt();

    levelCollision = QVector< QVector<int> > (m);
    texMap = QVector< QVector<int> > (m);

    for(int i = 0; i < m; i++){
        QString line = file.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            int x = list.at(j).toInt();
            levelCollision[i].push_back(x);
        }
    }

    for(int i = 0; i < m; i++){
        QString line = file.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            int x = list.at(j).toInt();
            texMap[i].push_back(x);
        }
    }

    for(int i = 0; i < m; i++){
        QString line = file.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            int x = list.at(j).toInt();
            if(x){
                envItems.push_back(new AnimatedItem(Engine::getInstance().getAssetEnv(x - 1), mapToScene(matrixToMap(i, j)).x(), mapToScene(matrixToMap(i, j)).y(), i+j));
                this->addItem((envItems[envItems.size() - 1]));
            }
        }
    }


    charCollision = QVector< QVector<int> > (m);
    for(int i = 0; i < m; i++)
        charCollision[i] = QVector<int> (n);

    line = file.readLine().trimmed();
    int s = line.toInt();

    for(int i = 0; i < s; i++){
        line = file.readLine().trimmed();
        list = line.split(" ");
        int x = list.at(0).toInt();
        if(x == 1){
            CharTemplate character = Engine::getInstance().getTemplate(0);
            int posI = list.at(1).toInt();
            int posJ = list.at(2).toInt();
            player = new Player(this, character.health, character.speed, character.size, posI, posJ, Engine::getInstance().getAssetAnim(character.animIndex));
            addItem(player);
            charCollision[posI][posJ] = 1;
        }
        else {
            CharTemplate character = Engine::getInstance().getTemplate(x);
            int count = list.at(1).toInt();
            QVector< QPair<int, int> > route;
            for(int j = 0; j < count; j++)
                route.push_back(QPair<int, int>(list.at(2+2*j).toInt(), list.at(3+2*j).toInt()));

            enemies.push_back(new Enemy(this, character.health, character.speed, character.size, route, character.aggroRange, character.deaggroRange, Engine::getInstance().getAssetAnim(character.animIndex)));
            addItem(enemies[enemies.size() - 1]);
            for(int k = 0; k < character.size; k++)
                for(int l = 0; l < character.size; l++)
                    charCollision[route[0].first + k][route[0].second + l] = 1;
        }
    }

    for(int i = 0; i < texMap.length(); i++)
        for(int j = 0; j < texMap[i].length(); j++){
            QGraphicsPixmapItem* pic = this->addPixmap(Engine::getInstance().getAssetTiles(texMap[i][j]));
            pic->setOffset(-37, -19);
            pic->setPos(mapToScene(matrixToMap(i, j)).x(), mapToScene(matrixToMap(i, j)).y());
            pic->setZValue(-1);
        }
}

Player* Map::getPlayer(){
    return player;
}

void Map::setPlayer(Player* p) {
    player = p;
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mousePressEvent(event);

    if(event->button() == Qt::MouseButton::LeftButton){
        QPointF pressPos = event->buttonDownScenePos(Qt::MouseButton::LeftButton);
        QPair<int, int> newDest = mapToMatrix(QVector2D(0.5, 0.5) + sceneToMap(QVector2D(pressPos.x(), pressPos.y())));
        player->setDestination(newDest.first, newDest.second);
        player->setTarget(nullptr);
    }

}

QVector2D Map::mapToScene(QVector2D worldCoords){
    QVector2D cameraPos = QVector2D(1.5, 1.5);
    QVector2D sceneCenter = QVector2D(150, 150);

    QVector2D translate = worldCoords - cameraPos;

    float x = (translate.x() - translate.y())/sqrt(2);
    float y = 0.5 * (translate.x() + translate.y())/sqrt(2);
    QVector2D vektor = QVector2D(x, y);

    vektor *= 50;

    return  vektor + sceneCenter;
}

QVector2D Map::sceneToMap(QVector2D sceneCoords){
    QVector2D cameraPos = QVector2D(1.5, 1.5);
    QVector2D sceneCenter = QVector2D(150, 150);

    QVector2D translate = sceneCoords - sceneCenter;

    float x = (translate.x() + 2 * translate.y())/sqrt(2);
    float y = (2 * translate.y() - translate.x())/sqrt(2);

    QVector2D vektor = QVector2D(x, y);

    vektor *= 0.02;

    return vektor + cameraPos;
}

QVector2D Map::matrixToMap(int i, int j){
    return QVector2D(j + 0.5, i + 0.5);
}

QPair<int, int> Map::mapToMatrix(QVector2D worldCoords){
    return QPair<int, int>(worldCoords.y() - 0.5, worldCoords.x() - 0.5);
}

void Map::setCam(Camera *camera){
    this->player->setCam(camera);
}

void Map::moveCharacter(Character &ch, int destX, int destY){
    int starti = ch.getI();
    int startj = ch.getJ();
    int width = ch.getSize();

    for(int nexti = starti; nexti < starti + width; nexti++)
        for(int nextj = startj; nextj < startj + width; nextj++)
            charCollision[nexti][nextj] = 0;

    for(int nexti = destX; nexti < destX + width; nexti++)
        for(int nextj = destY; nextj < destY + width; nextj++)
            charCollision[nexti][nextj] = 1;
}

void Map::update(int deltaT){
    player->update(deltaT);
    for(int i = 0; i < enemies.size(); i++)
        enemies[i]->update(deltaT);
    for(int i = 0; i < envItems.size(); i++)
        envItems[i]->update(deltaT);
}

void Map::destroyEnemy(Enemy *enemy){
    enemies.removeOne(enemy);
    this->removeItem(enemy);
    if(player->getTarget() == enemy)
        player->setTarget(nullptr);

    for(int i = 0; i < enemy->getSize(); i++)
        for(int j = 0; j < enemy->getSize(); j++)
            charCollision[enemy->getI() + i][enemy->getJ() + j] = 0;

    delete enemy;
}

bool Map::exists(int i, int j){
    return i >= 0 && j >= 0 && i < levelCollision.size() && j < levelCollision[i].size();
}

// Nalazenje najkraceg puta implementirano pomocu BFS algoritma:
QPair<int, int> Map::findPath(Character& ch, int destI, int destJ){
    QVector< QVector<int> > dist = QVector< QVector<int> >(levelCollision);
    QQueue< QPair<int, int> > q;
    int starti = ch.getI();
    int startj = ch.getJ();
    int width = ch.getSize();

    // Provera koja su polja prohodna:
    for(int i = 0; i < dist.size(); i++)
        for(int j = 0; j < dist[i].size(); j++)
            if(levelCollision[i][j] || (charCollision[i][j] &&
                                        !(i >= starti && i < starti + width && j >= startj && j < startj + width)))
                // neprohodno polje
                dist[i][j] = -1;
            else
                // prohodno polje
                dist[i][j] = -2;

    q.enqueue(QPair<int, int>(starti, startj));
    dist[starti][startj] = 0;

    // Pronalazenje najkraceg puta, BFS algoritam:
    while(!q.empty()) {
        QPair<int, int> next = q.dequeue();

        for(int i = -1; i <= 1; i++)
            for(int j = -1; j <= 1; j++){
                bool noCollision = true;
                for(int nexti = next.first + i; nexti < next.first + width + i; nexti++)
                    for(int nextj = next.second + j; nextj < next.second + width + j; nextj++)
                        if(!exists(nexti, nextj) || dist[nexti][nextj] == -1)
                            noCollision = false;
                if(noCollision && dist[next.first + i][next.second + j] == -2){
                    dist[next.first + i][next.second + j] = dist[next.first][next.second] + 1;
                    q.enqueue(QPair<int, int>(next.first + i, next.second + j));
                }
                if(next.first + i == destI && next.second + j == destJ)
                    q.clear();
             }
    }

    if(dist[destI][destJ] == 0)
        return QPair<int, int>(ch.getI(), ch.getJ());

    if(dist[destI][destJ] < 0){
        bool indicator = false;
        int min;
        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(exists(destI + i, destJ + j) && dist[destI + i][destJ + j] >= 0){
                    if(!indicator) {
                        min = dist[destI + i][destJ + j];
                        indicator = true;
                    }
                    else if(min > dist[destI + i][destJ + j])
                        min = dist[destI + i][destJ + j];
                }
            }
        }
        if(!indicator || min == 0)
            return QPair<int, int>(ch.getI(), ch.getJ());
        dist[destI][destJ] = min + 1;
    }

    // Idemo od kraja:
    while(dist[destI][destJ] != 1){
        int nextI = destI;
        int nextJ = destJ;
        for(int t = 1, c = 0; c < 9; t = (t + 2) % 9, c++) {
            int i = t % 3 - 1;
            int j = t / 3 - 1;
            int tempI = destI + i;
            int tempJ = destJ + j;
            if(exists(tempI, tempJ) && dist[tempI][tempJ] == dist[destI][destJ] - 1){
                nextI = tempI;
                nextJ = tempJ;
                break;
            }
         }
        destI = nextI;
        destJ = nextJ;
    }

    return QPair<int, int>(destI, destJ);
}
