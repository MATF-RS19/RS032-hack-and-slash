#include "Character.h"

#include <QDebug>

Character::Character(Map* world, int coordX, int coordY, int height, int weight) : QGraphicsRectItem(coordX, coordY, height, weight) {
    this->world = world;

    worldCoords = QVector2D(1, 1);
    nextCellCoords = QVector2D(1, 1);
    movementSpeed = 0.001f;

    charState = ready;

    mapI = 1;
    mapJ = 1;

    destI = 1;
    destJ = 1;

    size = 1;
}

void Character::update(int deltaT){
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

    QVector2D sceneCoords = this->world->mapToScene(worldCoords + QVector2D(0.5, 0.5)) - QVector2D(50, 59);
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
    destI = i;
    destJ = j;
}
