#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>
#include <QPair>

class Character;
class Player;

class Map : public QGraphicsScene{
public:
    Map();
    QPair<int, int> findPath(Character& ch, int destX, int destY);
    bool exists(int i, int j);
    void moveCharacter(Character& ch, int destX, int destY);
    QVector2D mapToScene(QVector2D worldCoords);
    QVector2D sceneToMap(QVector2D sceneCoords);
    QVector2D matrixToMap(int i, int j);
    QPair<int, int> mapToMatrix(QVector2D worldCoords);
    void setPlayer(Player* p);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QVector< QVector<int> > levelCollision;
    QVector< QVector<int> > charCollision;

    Player* player;
};

#endif // MAP_H
