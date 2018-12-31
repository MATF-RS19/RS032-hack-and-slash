#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "Character.h"
#include "Camera.h"

class Player : public Character{
public:

    Player(Map* m, int x, int y, Animator anim) : Character(m, x, y, anim) {}
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    PositionX checkPositionX(float destX, float destY);
    PositionY checkPositionY(float destX, float destY);
    void update(int deltaT) override;
    void setCam(Camera* camera);

private:
     Camera* cam;
     PositionX posX;
     PositionY posY;
};


#endif // PLAYER_H
