#include "Player.h"

#include <QDebug>
#include <cmath>

#include "Camera.h"

void Player::mousePressEvent(QGraphicsSceneMouseEvent* event) {

}

void Player::keyPressEvent(QKeyEvent* event) {

}

void Player::update(int deltaT){
    Character::update(deltaT);

    cam->ensureVisible(this, cam->getBorderX(), cam->getBorderY());
}

void Player::cast(int i) {
    if(spells[i]->ready() && spells[i]->getManaCost() <= mana) {
        switch(spells[i]->getType()) {
        case Spell::noTarget:
            spells[i]->cast(this);
            break;
        case Spell::characterTarget:
            world->setInputState(Map::InputState::targetCharacter, i);
            break;
        case Spell::mapTarget:
            world->setInputState(Map::InputState::targetMap, i);
            break;
        }
        charState = ready;
    }
}

void Player::setCam(Camera* camera){
    cam = camera;
}

Camera* Player::getCam() {
    return cam;
}

