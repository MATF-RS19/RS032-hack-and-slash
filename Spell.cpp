#include "Spell.h"

#include "Engine.h"
#include "Map.h"

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
}

void FireballSpell::cast(Character* caster, Character* target){
    if(ready() && caster->getMana() >= manaCost && QVector2D(caster->getWorldCoords() - target->getWorldCoords()).length() < range){
        caster->drainMana(manaCost);
        FireballEffect* effect = new FireballEffect(caster, target, Engine::getInstance().getAssetSpell(animIndex), caster->getMap());

        caster->getMap()->addItem(effect);
        caster->getMap()->addSpell(effect);

        cooldownTimer = cooldown;
    }
}

FireballEffect::FireballEffect(Character* caster, Character* target, Animator animator, Map* m)
    : SpellEffect(caster, animator, m, caster->getWorldCoords().x(), caster->getWorldCoords().y())
{
    this->target = target;
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

        QVector2D dest = m->mapToScene(QVector2D(worldX, worldY));
        setPos(dest.x(), dest.y());
        setZValue(worldX + worldY);
    }
    else {
        m->destroySpell(this);
    }
}


