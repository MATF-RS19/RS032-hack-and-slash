#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "Character.h"
#include "Camera.h"

class Player : public Character{
public:

    Player(Map* m, float speed, int size, int x, int y, Animator anim) : Character(m, speed, size, x, y, anim) {}
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void update(int deltaT) override;
    void setCam(Camera* camera);

private:
     Camera* cam;
};


#endif // PLAYER_H
