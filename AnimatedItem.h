#ifndef ANIMATEDITEM_H
#define ANIMATEDITEM_H

#include <QGraphicsPixmapItem>
#include "Animator.h"

class AnimatedItem: public QGraphicsPixmapItem{
public:
    AnimatedItem(Animator animator, int posX, int posY, int posZ);
    void update(int deltaT);
private:
    Animator animator;
};

#endif // ANIMATEDITEM_H
