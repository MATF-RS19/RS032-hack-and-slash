#include "Player.h"

void Player::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QPointF pressPos = event->buttonDownScenePos(Qt::MouseButton::LeftButton);
    QPair<int, int> newDest = world->mapToMatrix(world->sceneToMap(QVector2D(pressPos.x(), pressPos.y())));
    setDestination(newDest.first, newDest.second);
}
