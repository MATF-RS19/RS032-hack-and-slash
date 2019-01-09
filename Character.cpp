#include "Character.h"

#include <QDebug>
#include <QPointF>
#include <QVector2D>

#include "Spell.h"

Character::Character(Map* world, int health, float speed, int size, int coordI, int coordJ, Animator animator, QVector<Spell*> spells): QGraphicsPixmapItem (){
    this->setPixmap(animator.getCurrentFrame());

    this->world = world;

    this->animator = animator;

    worldCoords = world->matrixToMap(coordI, coordJ);
    nextCellCoords = world->matrixToMap(coordI, coordJ);
    movementSpeed = speed;

    charState = ready;

    mapI = coordI;
    mapJ = coordJ;

    destI = coordI;
    destJ = coordJ;

    this->size = size;

    orientation = 0;
    attackRange = 1.5;
    attackCooldown = 2000;
    attackTimer = 0;

    this->health = health;
    maxHealth = 300000;
    mana = 100;
    maxMana = 100;
    attackDmg = 10;

    this->spells = spells;

    setOffset(-animator.getOffsetX(), -animator.getOffsetY());
    QVector2D pos = world->mapToScene(worldCoords);
    setPos(pos.x(), pos.y());
}

void Character::update(int deltaT){
    for(int i = 0; i < spells.size(); i++)
        spells[i]->update(deltaT);

    setZValue(worldCoords.x() + worldCoords.y());
    orient();

    animator.setDefaultAnimation(orientation);
    bool loops = animator.update(deltaT);

    bool dealDmg = false;

    if(charState == moving)
        animator.setCurrentAnimation(8 + orientation);
    else if(charState == ready)
        animator.setCurrentAnimation(orientation);
    else if(charState == attacking){
        if(!loops){
            dealDmg = true;
            charState = attacked;
        }
        else
            animator.setCurrentAnimation(16 + orientation);
    }

    QPixmap frame = animator.getCurrentFrame();
    this->setPixmap(frame);

    if(charState == moving){
        QVector2D v(nextCellCoords - worldCoords);
        if(v.length() < movementSpeed * deltaT * 2) {
            charState = ready;
            worldCoords = nextCellCoords;
        }
        else{
            v.normalize();
            worldCoords += movementSpeed * deltaT * v;
        }
    }
    if(charState == ready){
        if(target != nullptr){
            double dist = sqrt(pow(target->getI() - getI(), 2) + pow(target->getJ() - getJ(), 2));
            if(dist < attackRange && attackTimer == 0) {
                charState = attacking;
                destI = getI();
                destJ = getJ();
            }
            else{
                charState = ready;
                setDestination(target->getI(), target->getJ());
            }
        }

        if(mapI != destI || mapJ != destJ){
            QPair<int, int> nextCell = world->findPath(*this, destI, destJ);
            if(nextCell.first != mapI || nextCell.second != mapJ){
                world->moveCharacter(*this, nextCell.first, nextCell.second);
                mapI = nextCell.first;
                mapJ = nextCell.second;
                charState = moving;
                nextCellCoords = world->matrixToMap(nextCell.first, nextCell.second);
            }
        }
    }

    if(attackTimer || charState == attacking){
        attackTimer += deltaT;
        if(attackTimer > attackCooldown)
            attackTimer = 0;
    }

    if(charState == attacked){
        if(dealDmg && target){
            target->takeDmg(attackDmg);
        }
        if(attackTimer == 0)
            charState = ready;
    }

    QVector2D sceneCoords = this->world->mapToScene(worldCoords);
    setPos(sceneCoords.x(), sceneCoords.y());
}

Map* Character::getMap(){
    return world;
}

QVector2D Character::getWorldCoords(){
    return worldCoords;
}

int Character::getMana() {
    return mana;
}

void Character::orient(){
    QVector2D direction;

    if(charState == moving)
        direction = QVector2D(nextCellCoords - worldCoords);
    else if(charState == attacking && target != nullptr)
        direction = QVector2D(target->worldCoords - worldCoords);

    if(direction.length() < 0.01)
        return;
    direction.normalize();

    double s = sqrt(2)/2;

    if((direction - QVector2D(1, 0)).length() < 0.01)
        orientation = 1;
    if((direction - QVector2D(s, s)).length() < 0.5)
        orientation = 2;
    if((direction - QVector2D(0, 1)).length() < 0.01)
        orientation = 3;
    if((direction - QVector2D(-s, s)).length() < 0.5)
        orientation = 4;
    if((direction - QVector2D(-1, 0)).length() < 0.01)
        orientation = 5;
    if((direction - QVector2D(-s, -s)).length() < 0.5)
        orientation = 6;
    if((direction - QVector2D(0, -1)).length() < 0.01)
        orientation = 7;
    if((direction - QVector2D(s, -s)).length() < 0.5)
        orientation = 0;
}

void Character::takeDmg(int dmg){
    health -= dmg;
    if(health <= 0)
        charState = dead;
    qDebug() << "dmg dealt to" << this;
}

void Character::drainMana(int amount) {
    mana -= amount;
    if(mana < 0)
        mana = 0;
}

void Character::heal(int hp){
    health += hp;
    if(health > maxHealth)
        health = maxHealth;
}

int Character::getHealth(){
    return health;
}

void Character::cast(int i, Character* target) {
    spells[i]->cast(this, target);
}

void Character::cast(int i, float worldX, float worldY) {
    spells[i]->cast(this, worldX, worldY);
}

void Character::setTarget(Character* target){
    this->target = target;
}

Character* Character::getTarget() {
    return target;
}

int Character::getI(){
    return mapI;
}

int Character::getJ(){
    return mapJ;
}

int Character::getSize(){
    return size;
}

void Character::setDestination(int i, int j) {
    if(world->exists(i, j)){
        destI = i;
        destJ = j;
    }
}
