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
    void setCooldownTimer(int timer);
    virtual QString icon() { return ""; }

    virtual ~Spell() {}

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
    virtual void onCharacterDeath(Character* character) {}

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
    void cast(Character* caster, Character* target) override;
    QString icon() override { return ":/Assets/UI/Icons/fireball.png"; }

    ~FireballSpell() override {}

private:
    float range = 4;
};

class FireballEffect: public SpellEffect {
public:
    FireballEffect(Character* caster, Character* target, Animator animator, Map* m);
    void update(int deltaT) override;
    void onCharacterDeath(Character* character) override;

private:
    Character* target;
    float speed = 0;
    int dmg = 10;
};

class FirestormSpell: public Spell {
public:
    FirestormSpell()
        : Spell(8000, 15, 1, mapTarget)
    {}
    void cast(Character* caster, float worldX, float worldY) override;
    QString icon() override { return ":/Assets/UI/Icons/firestorm.png"; }

    ~FirestormSpell() override {}

private:
    float range = 3;
};

class FirestormEffect: public SpellEffect {
public:
    FirestormEffect(Character* caster, float worldX, float worldY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int dmg = 20;
    QVector< AnimatedItem* > items;
    float radius = 1.5f;
    int timer = 2400;
};

class DarkfogSpell: public Spell {
public:
    DarkfogSpell()
        : Spell(2500, 15, 7, mapTarget)
    {}
    void cast(Character* caster, float worldX, float worldY) override;
    QString icon() override { return ":/Assets/UI/Icons/darkfog.png"; }

    ~DarkfogSpell() override {}

private:
    float range = 4;
};

class DarkfogEffect: public SpellEffect {
public:
    DarkfogEffect(Character* caster, float worldX, float worldY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int dmg = 3;
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
    QString icon() override { return ":/Assets/UI/Icons/darkorbs.png"; }

    ~DarkorbsSpell() override {}
};

class DarkorbsEffect: public SpellEffect{
public:
    DarkorbsEffect(Character* caster, float displacementX, float displacementY, Animator animator, Map* m);
    void update(int deltaT) override;
    void onCharacterDeath(Character* character) override;

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
    QString icon() override { return ":/Assets/UI/Icons/heal.png"; }

    ~HealSpell() override {}
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
    void cast(Character* caster, float worldX, float worldY) override;
    QString icon() override { return ":/Assets/UI/Icons/darkbead.png"; }

    ~DarkbeadSpell() override {}
};

class DarkbeadEffect: public SpellEffect {
public:
    DarkbeadEffect(Character* caster, float directionX, float directionY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 2000;
    int dmg = 30;
    QVector2D direction;
    float speed = 0.01f;
    float radius = 0.5f;
};

class FlamethrowerSpell: public Spell {
public:
    FlamethrowerSpell()
        : Spell(2500, 15, 2, mapTarget)
    {}
    void cast(Character* caster, float worldX, float worldY) override;
    QString icon() override { return ":/Assets/UI/Icons/flamethrower.png"; }

    ~FlamethrowerSpell() override {}
};

class FlamethrowerEffect: public SpellEffect {
public:
    FlamethrowerEffect(Character* caster, float posX, float posY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 640;
    int dmg = 30;
    float radius = 0.5f;
};

class SlowSpell: public Spell {
public:
    SlowSpell()
        : Spell(2500, 15, 3, mapTarget)
    {}
    void cast(Character* caster, float worldX, float worldY) override;
    QString icon() override { return ":/Assets/UI/Icons/slow.png"; }

    ~SlowSpell() override {}

private:
    float range = 4;
};

class SlowEffect: public SpellEffect {
public:
    SlowEffect(Character* caster, float directionX, float directionY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 10000;
    float speed = 0.0005f;
    float radius = 2;
};

class SilenceSpell: public Spell {
public:
    SilenceSpell()
        : Spell(2500, 15, 8, mapTarget)
    {}
    void cast(Character* caster, float worldX, float worldY) override;
    QString icon() override { return ":/Assets/UI/Icons/silence.png"; }

    ~SilenceSpell() override {}

private:
    float range = 4;
};

class SilenceEffect: SpellEffect {
public:
    SilenceEffect(Character* caster, float directionX, float directionY, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 640;
    int cooldownEffect = 10000;
    float radius = 2;
};

class ShieldSpell: public Spell {
public:
    ShieldSpell()
        : Spell(2500, 15, 0, noTarget)
    {}
    void cast(Character* caster) override;
    QString icon() override { return ":/Assets/UI/Icons/shield.png"; }

    ~ShieldSpell() override {}

};

class ShieldEffect: public SpellEffect {
public:
    ShieldEffect(Character* caster, Animator animator, Map* m);
    void update(int deltaT) override;

private:
    int timer = 5000;
};

#endif // SPELL_H
