#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QVector2D>
#include <QPair>
#include <QVector>

#include "Map.h"
#include "Animator.h"

class Camera;

class Character : public QGraphicsPixmapItem{
public:
    Character(Map* world, float speed, int size, int coordI, int coordJ, Animator animator);
    virtual void update(int deltaT);
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

    Animator animator;
};


#endif // CHARACTER_H
