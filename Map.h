#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>
#include <QPair>
#include <QString>

class Character;
class Player;
class AnimatedItem;
class Enemy;
class Camera;

class Map : public QGraphicsScene{
public:
    Map(QString levelName);
    QPair<int, int> findPath(Character& ch, int destX, int destY);
    bool exists(int i, int j);
    void moveCharacter(Character& ch, int destX, int destY);
    QVector2D mapToScene(QVector2D worldCoords);
    QVector2D sceneToMap(QVector2D sceneCoords);
    QVector2D matrixToMap(int i, int j);
    QPair<int, int> mapToMatrix(QVector2D worldCoords);
    void setPlayer(Player* p);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void update(int deltaT);
    Player* getPlayer();
    void setCam(Camera* camera);

private:
    QVector< QVector<int> > levelCollision;
    QVector< QVector<int> > charCollision;
    QVector< QVector<int> > texMap;

    Player* player;
    QVector< Enemy* > enemies;
    QVector< AnimatedItem* > envItems;
};

#endif // MAP_H
