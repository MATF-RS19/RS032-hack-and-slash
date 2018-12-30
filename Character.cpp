#include "Character.h"

#include <QDebug>
#include <QPointF>
#include <QVector2D>

Character::Character(Map* world, int coordI, int coordJ, int offsetX, int offsetY, Animator animator) : QGraphicsPixmapItem (){
    this->setPixmap(animator.getCurrentFrame());

    this->world = world;

    this->animator = animator;

    worldCoords = world->matrixToMap(coordI, coordJ);
    nextCellCoords = world->matrixToMap(coordI, coordJ);
    movementSpeed = 0.001f;

    charState = ready;

    mapI = 1;
    mapJ = 1;

    destI = 1;
    destJ = 1;

    size = 1;

    setOffset(-offsetX, -offsetY);
    QVector2D pos = world->mapToScene(worldCoords);
    setPos(pos.x(), pos.y());
}

void Character::update(int deltaT){
    if(charState == moving || destI != mapI || destJ != mapJ){
        QVector2D direction(world->mapToScene(nextCellCoords) - world->mapToScene(worldCoords));
        direction.normalize();
        if((direction - QVector2D(1, 0)).length() < 0.01)
            animator.setCurrentAnimation(1);
        if((direction - QVector2D(0.7, 0.7)).length() < 0.5)
            animator.setCurrentAnimation(3);
        if((direction - QVector2D(0, 1)).length() < 0.01)
            animator.setCurrentAnimation(5);
        if((direction - QVector2D(-0.7, 0.7)).length() < 0.5)
            animator.setCurrentAnimation(7);
        if((direction - QVector2D(-1, 0)).length() < 0.01)
            animator.setCurrentAnimation(9);
        if((direction - QVector2D(-0.7, -0.7)).length() < 0.5)
            animator.setCurrentAnimation(11);
        if((direction - QVector2D(0, -1)).length() < 0.01)
            animator.setCurrentAnimation(13);
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
