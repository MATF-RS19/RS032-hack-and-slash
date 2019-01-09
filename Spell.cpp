#include "Spell.h"

#include "Engine.h"
#include "Map.h"

#include <QtMath>

void Spell::update(int deltaT) {
    cooldownTimer -= deltaT;
    if(cooldownTimer <= 0)
        cooldownTimer = 0;
}

bool Spell::ready() {
    return cooldownTimer == 0;
}

Spell::CastType Spell::getType() {
    return castType;
}

int Spell::getManaCost() {
    return manaCost;
}

void SpellEffect::update(int deltaT) {
    animator.update(deltaT);
    setPixmap(animator.getCurrentFrame());

    QVector2D pos = m->mapToScene(QVector2D(worldX, worldY));
    setPos(pos.x(), pos.y());
    setZValue(worldX + worldY);

}
void FireballSpell::cast(Character* caster, Character* target){
    if(ready() && caster->getMana() >= manaCost && QVector2D(caster->getWorldCoords() - target->getWorldCoords()).length() < range){
        caster->drainMana(manaCost);
        FireballEffect* effect = new FireballEffect(caster, target, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());



        cooldownTimer = cooldown;
    }
}

FireballEffect::FireballEffect(Character* caster, Character* target, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, caster->getWorldCoords().x(), caster->getWorldCoords().y())
{
    this->target = target;

    m->addItem(this);
    m->addSpell(this);
}

void FireballEffect::update(int deltaT){
    SpellEffect::update(deltaT);
    //proveri da li target postoji, if(target) nije dovoljno !!!
    if(target){
        QVector2D direction = QVector2D(target->getWorldCoords() - QVector2D(worldX, worldY));
        if(direction.length() < speed * deltaT * 2) {
            target->takeDmg(dmg);
            target = nullptr;
        }
        else{
            direction.normalize();
            worldX += speed * deltaT * direction.x();
            worldY += speed * deltaT * direction.y();
            speed += 0.00005 * deltaT;
        }
    }
    else {
        m->destroySpell(this);
    }
}

void FirestormSpell::cast(Character *caster, float worldX, float worldY){
    QVector2D pos = caster->getMap()->mapToScene(QVector2D(worldX, worldY));
    if(ready() && caster->getMana() >= manaCost && (caster->getWorldCoords() - QVector2D(worldX, worldY)).length() < range ){
        caster->drainMana(manaCost);

        FirestormEffect* effect = new FirestormEffect(caster, worldX, worldY, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());

        cooldownTimer = cooldown;
    }

}

FirestormEffect::FirestormEffect(Character* caster, float worldX, float worldY, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, worldX, worldY)
{
    m->addItem(this);
    m->addSpell(this);

    for(int i = 0; i < 6; i++){
        QVector2D v = QVector2D(cos(i * M_PI/3), sin(i * M_PI/3));
        QVector2D pos = m->mapToScene(QVector2D(worldX, worldY) + 0.75* radius * v);
        items.push_back(new AnimatedItem(animator, pos.x(), pos.y(), worldX + worldY + 0.75*radius*(v.x() + v.y())));

    }

    for(int i = 0; i < items.size(); i++){
        m->addItem(items[i]);
    }

    for(int i = 0; i < m->numberOfEnemies(); i++){
        Character* enemy = m->getEnemy(i);
        QVector2D enemyPos = enemy->getWorldCoords();
        if(enemyPos.x() <= worldX + radius && enemyPos.y() <= worldY + radius)
            enemy->takeDmg(dmg);
    }
}

void FirestormEffect::update(int deltaT){
    SpellEffect::update(deltaT);
    for(int i = 0; i < items.size(); i++)
        items[i]->update(deltaT);

    timer -= deltaT;
    if(timer <= 0){
        for(int i = 0; i < items.size(); i++) {
            m->removeItem(items[i]);
            delete items[i];
        }
        m->destroySpell(this);
        return;
    }
}

void DarkfogSpell::cast(Character* caster, float worldX, float worldY){
    if(ready() && caster->getMana() >= manaCost && (caster->getWorldCoords() - QVector2D(worldX, worldY)).length() < range ){
        caster->drainMana(manaCost);

        DarkfogEffect* effect = new DarkfogEffect(caster, worldX, worldY, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());

        cooldownTimer = cooldown;
    }
}

DarkfogEffect::DarkfogEffect(Character* caster, float worldX, float worldY, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, worldX, worldY)
{
    m->addItem(this);
    m->addSpell(this);
}

void DarkfogEffect::update(int deltaT){
    SpellEffect::update(deltaT);
    setZValue(worldX + worldY + 2);

    tickTimer -= deltaT;
    if(tickTimer <= 0){
        for(int i = 0; i < m->numberOfEnemies(); i++){
            Character* enemy = m->getEnemy(i);
            QVector2D enemyPos = enemy->getWorldCoords();
            if(enemyPos.x() <= worldX + radius && enemyPos.y() <= worldY + radius)
                enemy->takeDmg(dmg);
        }
        tickTimer = 500;
    }

    timer -= deltaT;
    if(timer <= 0){
        m->destroySpell(this);
        return;
    }
}


