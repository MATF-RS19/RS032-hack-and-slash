#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "Character.h"

class Player : public Character{
public:
    Player(Map* m, int x, int y, int w, int h) : Character(m,x,y,w,h) {}
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};


#endif // PLAYER_H
