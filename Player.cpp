#include "Player.h"

#include <cmath>

void Player::mousePressEvent(QGraphicsSceneMouseEvent* event) {

}

void Player::update(int deltaT){


    Character::update(deltaT);
    cam->ensureVisible(this, cam->getBorderX(), cam->getBorderY());
}

void Player::setCam(Camera* camera){
    cam = camera;
}

