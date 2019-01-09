#ifndef SPELL_H
#define SPELL_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include "Animator.h"

class Character;
class Map;

class Spell {
public:
    enum CastType {
        noTarget,
        characterTarget,
        mapTarget
    };

    Spell() {}
    Spell(int cooldown, int manaCost, int animIndex, CastType castType)
        : cooldown(cooldown), manaCost(manaCost), animIndex(animIndex), castType(castType)
    {}
    virtual void cast(Character* caster) {}
    virtual void cast(Character* caster, Character* target) {}
    virtual void cast(Character* caster, float worldX, float worldY) {}
    void update(int deltaT);
    bool ready();
    CastType getType();
    int getManaCost();

protected:
    int cooldown;
    int cooldownTimer = 0;

    int manaCost;

    int animIndex;
    CastType castType;
};

class SpellEffect: public QGraphicsPixmapItem {
public:
    SpellEffect(Character* caster, Animator animator, Map* m, float worldX, float worldY)
        : caster(caster), animator(animator), m(m), worldX(worldX), worldY(worldY)
    {setOffset(-animator.getOffsetX(), -animator.getOffsetY()); }
    virtual void update(int deltaT);

protected:
    float worldX, worldY;

    Animator animator;
    Character* caster;
    Map* m;
};

class FireballSpell: public Spell {
public:
    FireballSpell()
        : Spell(2500, 15, 4, characterTarget)
    {}
    void cast(Character* caster) override {}
    void cast(Character* caster, Character* target) override;
    void cast(Character* caster, float worldX, float worldY) override {}

private:
    float range = 4;
};

class FireballEffect: public SpellEffect {
public:
    FireballEffect(Character* caster, Character* target, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    Character* target;
    float speed = 0;
    float dmg = 10;
};





#endif // SPELL_H
