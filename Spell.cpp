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

void DarkorbsSpell::cast(Character* caster){
    if(ready() && caster->getMana() >= manaCost){
        caster->drainMana(manaCost);

        for(int i = 0; i < 3; i++){
            QVector2D v = 0.5 * QVector2D(cos(i * 2*M_PI/3), sin(i * 2*M_PI/3));
            new DarkorbsEffect(caster, v.x(), v.y(), Engine::getInstance().getAssetSpell(animIndex), caster->getMap());
        }

        cooldownTimer = cooldown;
    }
}

DarkorbsEffect::DarkorbsEffect(Character* caster, float displacementX, float displacementY, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, caster->getWorldCoords().x() + displacementX, caster->getWorldCoords().y() + displacementY)
{
    this->displacementX = displacementX;
    this->displacementY = displacementY;
    m->addItem(this);
    m->addSpell(this);
}

void DarkorbsEffect::update(int deltaT){
    SpellEffect::update(deltaT);

    // da li postoji, nije dovoljno !target
    if(!target){
        worldX = caster->getWorldCoords().x() + displacementX;
        worldY = caster->getWorldCoords().y() + displacementY;

        for(int i = 0; i < m->numberOfEnemies(); i++){
            Character* enemy = m->getEnemy(i);
            if((enemy->getWorldCoords()- caster->getWorldCoords() - QVector2D(displacementX, displacementY)).length() < radius){
                target = enemy;
            }
        }
    }
    else {
        QVector2D direction = QVector2D(target->getWorldCoords() - QVector2D(worldX, worldY));
        if(direction.length() < speed * deltaT * 2) {
            target->takeDmg(dmg);
            target = nullptr;
            m->destroySpell(this);
        }
        else{
            direction.normalize();
            worldX += speed * deltaT * direction.x();
            worldY += speed * deltaT * direction.y();
            speed += 0.00001 * deltaT;
        }
    }
}

void HealSpell::cast(Character* caster){
    if(ready() && caster->getMana() >= manaCost){
        caster->drainMana(manaCost);

        HealEffect* effect = new HealEffect(caster, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());

        cooldownTimer = cooldown;
    }
}

HealEffect::HealEffect(Character* caster, Animator animator, Map* m)
    : SpellEffect (caster, animator, m, caster->getWorldCoords().x(), caster->getWorldCoords().y())
{
    m->addItem(this);
    m->addSpell(this);

    caster->heal(hp);
}

void HealEffect::update(int deltaT){
    SpellEffect::update(deltaT);

    setZValue(this->zValue() - 0.1);
    timer -= deltaT;
    if(timer <= 0){
        m->destroySpell(this);
        return;
    }
}

void DarkbeadSpell::cast(Character* caster, float worldX, float worldY){
    if(ready() && caster->getMana() >= manaCost){
        caster->drainMana(manaCost);

        QVector2D dir = (QVector2D(worldX, worldY) - caster->getWorldCoords()).normalized();
        for(int i = -1; i <= 1; i++){
            float dirX = dir.x() * cos(2*i*M_PI/9) - dir.y() * sin(2*i*M_PI/9);
            float dirY = dir.x() * sin(2*i*M_PI/9) + dir.y() * cos(2*i*M_PI/9);
            new DarkbeadEffect(caster, dirX, dirY, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());
        }
        cooldownTimer = cooldown;
    }
}

DarkbeadEffect::DarkbeadEffect(Character* caster, float directionX, float directionY, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, caster->getWorldCoords().x(), caster->getWorldCoords().y())
{
    this->direction = QVector2D(directionX, directionY);

    m->addItem(this);
    m->addSpell(this);
}

void DarkbeadEffect::update(int deltaT){
    SpellEffect::update(deltaT);

    timer -= deltaT;
    if(timer <= 0){
        m->destroySpell(this);
        return;
    }

    worldX += speed * deltaT * direction.x();
    worldY += speed * deltaT * direction.y();

    for(int i = 0; i < m->numberOfEnemies(); i++){
        Character* enemy = m->getEnemy(i);
        if((QVector2D(worldX, worldY) - enemy->getWorldCoords()).length() < radius){
            enemy->takeDmg(dmg);
            m->destroySpell(this);
            return;
        }
    }
}

void FlamethrowerSpell::cast(Character* caster, float worldX, float worldY){
    if(ready() && caster->getMana() >= manaCost){
        caster->drainMana(manaCost);

        QVector2D dir = (QVector2D(worldX, worldY) - caster->getWorldCoords()).normalized();
        for(int i = 0; i < 4; i++){
            float dirX = caster->getWorldCoords().x() + (i+1)*0.5*dir.x();
            float dirY = caster->getWorldCoords().y() + (i+1)*0.5*dir.y();
            new FlamethrowerEffect(caster, dirX, dirY, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());
        }
        cooldownTimer = cooldown;
    }
}

FlamethrowerEffect::FlamethrowerEffect(Character* caster, float posX, float posY, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, posX, posY)
{
    for(int i = 0; i < m->numberOfEnemies(); i++){
        Character* enemy = m->getEnemy(i);
        if((QVector2D(worldX, worldY) - enemy->getWorldCoords()).length() < radius){
            enemy->takeDmg(dmg);
        }
    }

    m->addItem(this);
    m->addSpell(this);
}

void FlamethrowerEffect::update(int deltaT){
    SpellEffect::update(deltaT);

    timer -= deltaT;
    if(timer <= 0){
        m->destroySpell(this);
        return;
    }
}




