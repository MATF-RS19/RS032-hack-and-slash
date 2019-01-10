#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "Character.h"
#include "Camera.h"

class Player : public Character{
public:
    Player(Map* m, int health, float speed, int size, int x, int y, Animator anim, QVector<Spell*> spells) : Character(m, health, speed, size, x, y, anim, spells) {}
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void update(int deltaT) override;
    void setCam(Camera* camera);
    Camera* getCam();
    void cast(int i);

private:
     Camera* cam;
};


#endif // PLAYER_H
