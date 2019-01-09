#ifndef SPELL_H
#define SPELL_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QVector2D>

#include "Animator.h"
#include "AnimatedItem.h"

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

class FirestormSpell: public Spell {
public:
    FirestormSpell()
        : Spell(8000, 15, 1, mapTarget)
    {}
    void cast(Character* caster) override {}
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override;

private:
    float range = 3;
};

class FirestormEffect: public SpellEffect {
public:
    FirestormEffect(Character* caster, float worldX, float worldY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    float dmg = 20;
    QVector< AnimatedItem* > items;
    float radius = 1.5;
    int timer = 2000;
};

class DarkfogSpell: public Spell {
public:
    DarkfogSpell()
        : Spell(2500, 15, 7, mapTarget)
    {}
    void cast(Character* caster) override {}
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override;

private:
    float range = 4;
};

class DarkfogEffect: public SpellEffect {
public:
    DarkfogEffect(Character* caster, float worldX, float worldY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    float dmg = 3;
    float radius = 2;
    int timer = 10000;
    int tickTimer = 500;
};

class DarkorbsSpell: public Spell{
public:
    DarkorbsSpell()
        : Spell(2500, 15, 9, noTarget)
    {}
    void cast(Character* caster) override;
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override {}
};

class DarkorbsEffect: public SpellEffect{
public:
    DarkorbsEffect(Character* caster, float displacementX, float displacementY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    float displacementX, displacementY;
    int dmg = 30;
    float radius = 2;
    float speed = 0;
    Character* target = nullptr;
};

class HealSpell: public Spell {
public:
    HealSpell()
        : Spell(2500, 15, 5, noTarget)
    {}
    void cast(Character* caster) override;
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override {}
};

class HealEffect: public SpellEffect {
public:
    HealEffect(Character* caster, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int hp = 10;
    int timer = 640;
};

class DarkbeadSpell: public Spell {
public:
    DarkbeadSpell()
        : Spell(2500, 15, 6, mapTarget)
    {}
    void cast(Character* caster) override {}
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override;

};

class DarkbeadEffect: public SpellEffect {
public:
    DarkbeadEffect(Character* caster, float directionX, float directionY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 2000;
    int dmg = 30;
    QVector2D direction;
    float speed = 0.01;
    float radius = 0.5;
};

class FlamethrowerSpell: public Spell {
public:
    FlamethrowerSpell()
        : Spell(2500, 15, 2, mapTarget)
    {}
    void cast(Character* caster) override {}
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override;

};

class FlamethrowerEffect: public SpellEffect {
public:
    FlamethrowerEffect(Character* caster, float posX, float posY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 640;
    int dmg = 30;
    float radius = 0.5;
};

class SlowSpell: public Spell {
public:
    SlowSpell()
        : Spell(2500, 15, 3, mapTarget)
    {}
    void cast(Character* caster) override {}
    void cast(Character* caster, Character* target) override {}
    void cast(Character* caster, float worldX, float worldY) override;

private:
    float range = 4;
};

class SlowEffect: public SpellEffect {
public:
    SlowEffect(Character* caster, float directionX, float directionY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 10000;
    float speed = 0.0005;
    float radius = 2;
};

#endif // SPELL_H
