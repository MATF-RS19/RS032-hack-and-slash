#include "Player.h"

void Player::mousePressEvent(QGraphicsSceneMouseEvent* event) {

}

void Player::update(int deltaT){
    Character::update(deltaT);

    if(target != nullptr)
        setDestination(target->getI(), target->getJ());

    cam->ensureVisible(this, cam->getBorderX(), cam->getBorderY());
}

void Player::setCam(Camera* camera){
    cam = camera;
}

