#include "Character.h"

#include <QDebug>
#include <QPointF>
#include <QVector2D>

Character::Character(Map* world, float speed, int size, int coordI, int coordJ, Animator animator) : QGraphicsPixmapItem (){
    this->setPixmap(animator.getCurrentFrame());

    this->world = world;

    this->animator = animator;

    worldCoords = world->matrixToMap(coordI, coordJ);
    nextCellCoords = world->matrixToMap(coordI, coordJ);
    movementSpeed = speed;

    charState = ready;

    mapI = coordI;
    mapJ = coordJ;

    destI = coordI;
    destJ = coordJ;

    this->size = size;

    setOffset(-animator.getOffsetX(), -animator.getOffsetY());
    QVector2D pos = world->mapToScene(worldCoords);
    setPos(pos.x(), pos.y());
}

void Character::update(int deltaT){
    setZValue(mapI + mapJ);
    if(charState == moving || destI != mapI || destJ != mapJ){
        QVector2D direction(world->mapToScene(nextCellCoords) - world->mapToScene(worldCoords));
        direction.normalize();
        if((direction - QVector2D(1, 0)).length() < 0.01)
            animator.setCurrentAnimation(8);
        if((direction - QVector2D(0.7, 0.7)).length() < 0.5)
            animator.setCurrentAnimation(9);
        if((direction - QVector2D(0, 1)).length() < 0.01)
            animator.setCurrentAnimation(10);
        if((direction - QVector2D(-0.7, 0.7)).length() < 0.5)
            animator.setCurrentAnimation(11);
        if((direction - QVector2D(-1, 0)).length() < 0.01)
            animator.setCurrentAnimation(12);
        if((direction - QVector2D(-0.7, -0.7)).length() < 0.5)
            animator.setCurrentAnimation(13);
        if((direction - QVector2D(0, -1)).length() < 0.01)
            animator.setCurrentAnimation(14);
        if((direction - QVector2D(0.7, -0.7)).length() < 0.5)
            animator.setCurrentAnimation(15);
    }
    else if(charState == ready){
        animator.setCurrentAnimation(0);
    }
    animator.update(deltaT);
    QPixmap frame = animator.getCurrentFrame();
    this->setPixmap(frame);

    if(charState == moving){
        QVector2D v(nextCellCoords - worldCoords);
        if(v.length() < movementSpeed * deltaT * 2) {
            charState = ready;
            worldCoords = nextCellCoords;
        }
        else{
            v.normalize();
            worldCoords += movementSpeed * deltaT * v;
        }
    }
    else if(charState == ready){
        if(mapI != destI || mapJ != destJ){
            QPair<int, int> nextCell = world->findPath(*this, destI, destJ);
            if(nextCell.first != mapI || nextCell.second != mapJ){
                world->moveCharacter(*this, nextCell.first, nextCell.second);
                mapI = nextCell.first;
                mapJ = nextCell.second;
                charState = moving;
                nextCellCoords = world->matrixToMap(nextCell.first, nextCell.second);
            }
            else {
                // ovo mozda valja ukloniti kasnije
                // ovo za sada radi tako da ako nema puta za dalje, zaustavlja se
                // umesto da ceka da se put otvori i da nastavi dalje
                destI = mapI;
                destJ = mapJ;
            }
        }
    }

    QVector2D sceneCoords = this->world->mapToScene(worldCoords);
    setPos(sceneCoords.x(), sceneCoords.y());
}


int Character::getI(){
    return mapI;
}

int Character::getJ(){
    return mapJ;
}

int Character::getSize(){
    return size;
}

void Character::setDestination(int i, int j) {
    if(world->exists(i, j)){
        destI = i;
        destJ = j;
    }
}
