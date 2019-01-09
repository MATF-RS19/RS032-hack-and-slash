#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include <QGraphicsPixmapItem>

class Consumable: public QGraphicsPixmapItem{
public:

private:
    int posI, posJ;


    struct ConsumItem{
        int maxHealth;
        int maxMana;
        int health;
        int mana;
        int attackDmg;
        int castDmg;
        int attackSpeed;
    };
    ConsumItem consitem;
};

#endif // CONSUMABLE_H
