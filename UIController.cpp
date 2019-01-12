#include "UIController.h"

#include "Map.h"
#include "Player.h"
#include "Engine.h"

CombatText::CombatText(int amount, bool dmg, float worldX, float worldY)
    : QGraphicsTextItem(QString::number(amount))
{

    setZValue(1000);
    setPos(double(worldX), double(worldY));
    if(dmg)
        setDefaultTextColor(Qt::red);
    else
        setDefaultTextColor(Qt::green);
}

void CombatText::update(int deltaT){
    timer -= deltaT;
    if(timer <= 0){
        UIController::getInstance().destroyCombatText(this);
        return;
    }

    setPos(pos() + QPointF(0, -0.01 * deltaT));
}

void UIController::newCombatText(int amount, bool dmg, float worldX, float worldY){
    QVector2D pos = Engine::getInstance().getMap()->mapToScene(QVector2D(worldX, worldY));
    combat.push_back(new CombatText(amount, dmg, pos.x(), pos.y() - 50));
    Engine::getInstance().getMap()->addItem(combat[combat.size()-1]);
}

void UIController::destroyCombatText(CombatText* text){
    Map* m = Engine::getInstance().getMap();

    m->removeItem(text);
    combat.removeOne(text);
    delete text;
}

UIController& UIController::getInstance(){
    static UIController instance;
    //instance.setMap(m)
    return instance;
}

UIController::UIController() {}

void UIController::load() {
    Map* m = Engine::getInstance().getMap();

    QPointF healthbarPos = Engine::getInstance().getCam()->mapToScene(10, 10);
    healthbarfull = new QGraphicsRectItem(healthbarPos.x(), healthbarPos.y(), 5 * m->getPlayer()->getMaxHealth(), 10);
    //healthbarfull->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    healthbarfull->setZValue(1000);
    healthbarfull->setBrush(Qt::gray);
    m->addItem(healthbarfull);

    healthbar = new QGraphicsRectItem(healthbarPos.x(), healthbarPos.y(), 5 * m->getPlayer()->getHealth(), 10);
    healthbar->setZValue(1001);
    healthbar->setBrush(Qt::red);
    m->addItem(healthbar);


    QPointF manabarPos = Engine::getInstance().getCam()->mapToScene(10, 25);
    manabarfull = new QGraphicsRectItem(manabarPos.x(), manabarPos.y(), 5 * m->getPlayer()->getMaxMana(), 10);
    //healthbarfull->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    manabarfull->setZValue(1000);
    manabarfull->setBrush(Qt::gray);
    m->addItem(manabarfull);

    manabar = new QGraphicsRectItem(manabarPos.x(), manabarPos.y(), 5 * m->getPlayer()->getMaxMana(), 10);
    manabar->setZValue(1001);
    manabar->setBrush(Qt::blue);
    m->addItem(manabar);

    //barBackground;

    QPointF spellbarPos = Engine::getInstance().getCam()->mapToScene(10, 1000);
    spellbar = new QGraphicsPixmapItem(QPixmap(":/Assets/UI/spellbar.png").scaledToWidth(300, Qt::SmoothTransformation));
    spellbar->setPos(spellbarPos);
    spellbar->setZValue(1003);
    m->addItem(spellbar);

    spellbarbg = new QGraphicsPixmapItem(QPixmap(":/Assets/UI/spellbarbg.png").scaledToWidth(300, Qt::SmoothTransformation));
    spellbarbg->setPos(spellbarPos);
    spellbarbg->setZValue(1000);
    m->addItem(spellbarbg);

    for(int i = 0; i < m->getPlayer()->numberOfSpells(); i++){
        QPointF iconPos = spellbarPos + QPointF(10 + 55 * i, 10);
        QGraphicsPixmapItem* icon = new QGraphicsPixmapItem(QPixmap(m->getPlayer()->getSpell(i)->icon()).scaledToWidth(55));
        icon->setPos(iconPos);
        icon->setZValue(1001);

        spells.push_back(icon);
        m->addItem(icon);
    }
}

void UIController::update(int deltaT) {
    Map* m = Engine::getInstance().getMap();

    QPointF healthbarPos = Engine::getInstance().getCam()->mapToScene(10, 10);
    healthbarfull->setRect(healthbarPos.x(), healthbarPos.y(), 5 * m->getPlayer()->getMaxHealth(), 10);
    healthbar->setRect(healthbarPos.x(), healthbarPos.y(), 5 * m->getPlayer()->getHealth(), 10);

    QPointF manabarPos = Engine::getInstance().getCam()->mapToScene(10, 25);
    manabarfull->setRect(manabarPos.x(), manabarPos.y(), 5 * m->getPlayer()->getMaxMana(), 10);
    manabar->setRect(manabarPos.x(), manabarPos.y(), 5 * m->getPlayer()->getMana(), 10);

    QPointF spellbarPos = Engine::getInstance().getCam()->mapToScene(10, 900);
    spellbar->setPos(spellbarPos);
    spellbarbg->setPos(spellbarPos);

    for(int i = 0; i < spells.size(); i++){
        QPointF iconPos = spellbarPos + QPointF(10 + 55 * i, 10);
        spells[i]->setPos(iconPos);
    }

    for(int i = 0; i < combat.size(); i++)
        combat[i]->update(deltaT);
}

void UIController::reset(){
    qDebug() << "reset begin";
    Map* m = Engine::getInstance().getMap();

    m->removeItem(healthbarfull);
    delete healthbarfull;

    m->removeItem(healthbar);
    delete healthbar;

    m->removeItem(manabarfull);
    delete manabarfull;

    m->removeItem(manabar);
    delete manabar;

//    m->removeItem(barBackground);
//    delete barBackground;

    m->removeItem(spellbar);
    delete spellbar;

    m->removeItem(spellbarbg);
    delete spellbarbg;

    for(int i = 0; i < spells.size(); i++){
        m->removeItem(spells[i]);
        delete spells[i];
    }
    spells.clear();

    for(int i = 0; i < combat.size(); i++){
        m->removeItem(combat[i]);
        delete combat[i];
    }
    combat.clear();

    qDebug() << "reset end";
}
