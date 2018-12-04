#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsRectItem>
#include <QVector2D>
#include <QPair>
#include <QVector>

#include "Map.h"

class Map;

class Character : public QGraphicsRectItem{
public:
    Character(Map* world, int coordX, int coordY, int height, int weight);
    void update(int deltaT);
    int getI();
    int getJ();
    int getSize();
    void setDestination(int i, int j);

protected:
    Map* world;

    QVector2D worldCoords;
    QVector2D nextCellCoords;
    float movementSpeed;

    int mapI, mapJ;         // koordinate polja matrice
    int destI, destJ;       // tamo gde treba doci


    int size;               // broj kvadrat
    enum State{
        moving,
        ready
    };
    State charState;
};


#endif // CHARACTER_H
