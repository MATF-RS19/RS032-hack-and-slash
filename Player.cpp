#include "Player.h"

#include <cmath>

#include "Camera.h"
#include "Engine.h"


void Player::update(int deltaT){
    Character::update(deltaT);

    regenTimer -= deltaT;
    if(regenTimer <= 0) {
        regenTimer = regenCooldown;
        heal(1);
        gainMana(1);
    }

    if(charState == dead){
        if(target)
            target = nullptr;
        Engine::getInstance().endGame();
        return;
    }

    Engine::getInstance().getCam()->focusOn(this);
}

void Player::cast(int i) {
    if(i < spells.count() && spells[i]->ready() && spells[i]->getManaCost() <= mana) {
        switch(spells[i]->getType()) {
        case Spell::noTarget:
            spells[i]->cast(this);
            break;
        case Spell::characterTarget:
            world->setInputState(Map::InputState::targetCharacter, i);
            break;
        case Spell::mapTarget:
            world->setInputState(Map::InputState::targetMap, i);
            break;
        }
        charState = ready;
    }
}


