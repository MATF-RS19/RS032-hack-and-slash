#include "Player.h"

void Player::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QPointF pressPos = event->buttonDownScenePos(Qt::MouseButton::LeftButton);
    QPair<int, int> newDest = world->mapToMatrix(QVector2D(0.5, 0.5) + world->sceneToMap(QVector2D(pressPos.x(), pressPos.y())));
    setDestination(newDest.first, newDest.second);
}

void Player::update(int deltaT){
    Character::update(deltaT);

    cam->ensureVisible(this, cam->getBorderX(), cam->getBorderY());
}

void Player::setCam(Camera* camera){
    cam = camera;
}
