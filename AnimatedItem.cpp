#include "AnimatedItem.h"

AnimatedItem::AnimatedItem(Animator animator, int posX, int posY, int posZ) : QGraphicsPixmapItem (){
    this->animator = animator;
    setOffset(-this->animator.getOffsetX(), -this->animator.getOffsetY());
    setPos(posX, posY);
    setZValue(posZ);
    setPixmap(this->animator.getCurrentFrame());
}

void AnimatedItem::update(int deltaT){
    if(animator.isAnimated()){
        animator.update(deltaT);
        setPixmap(animator.getCurrentFrame());
    }
}
