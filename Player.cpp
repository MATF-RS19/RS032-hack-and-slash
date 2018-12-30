#include "Player.h"
#include <QDebug>


void Player::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QPointF pressPos = event->buttonDownScenePos(Qt::MouseButton::LeftButton);
    QPair<int, int> newDest = world->mapToMatrix(QVector2D(0.5, 0.5) + world->sceneToMap(QVector2D(pressPos.x(), pressPos.y())));
    setDestination(newDest.first, newDest.second);
}


PositionX Player::checkPositionX(float destX, float destY){
    float dest = world->mapToScene(QVector2D(destX, destY)).x();
    float center = world->mapToScene(QVector2D(cam->getCameraX(), cam->getCameraY())).x();
    float border = cam->getBorderX();

    if(dest > center + border)
        return posright;
    else if(dest < center - border)
        return posleft;

    return posinsideX;
}

PositionY Player::checkPositionY(float destX, float destY){
    float dest = world->mapToScene(QVector2D(destX, destY)).y();
    float center = world->mapToScene(QVector2D(cam->getCameraX(), cam->getCameraY())).y();
    float border = cam->getBorderY();

    if(dest > center + border)
        return postop;
    else if(dest < center - border)
        return posdown;

    return posinsideY;
}

void Player::update(int deltaT){
    Character::update(deltaT);

    cam->ensureVisible(this, cam->getBorderX(), cam->getBorderY());
    //PositionX posX = checkPositionX(this->pos().x(), this->pos().y());
    //PositionY posY = checkPositionY(this->pos().x(), this->pos().y());

    //cam->update(posX, posY, world->mapToScene(worldCoords).x(), world->mapToScene(worldCoords).y());
}

void Player::setCam(Camera* camera){
    cam = camera;
}
