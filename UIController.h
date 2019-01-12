#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QLabel>
#include <QGraphicsItem>
#include <QButtonGroup>

#include "Player.h"
#include "Map.h"

class CombatText: public QGraphicsTextItem {
public:
    CombatText(int amount, bool dmg, float worldX, float worldY);
    void update(int deltaT);

private:
    int timer = 1000;
};

class UIController {
public:
    static UIController& getInstance();

    void update(int deltaT);
    void newCombatText(int amount, bool dmg, float worldX, float worldY);
    void destroyCombatText(CombatText* text);
    void reset();
    void load();

    UIController(UIController const&) = delete;
    void operator = (UIController const&) = delete;

private:
    UIController();

    QGraphicsRectItem* healthbarfull;
    QGraphicsRectItem* healthbar;
    QGraphicsRectItem* manabarfull;
    QGraphicsRectItem* manabar;
    QGraphicsPixmapItem* barBackground;
    QGraphicsPixmapItem* spellbar;
    QGraphicsPixmapItem* spellbarbg;
    QVector<QGraphicsPixmapItem*> spells;
    QVector<CombatText*> combat;
};

#endif // UICONTROLLER_H

