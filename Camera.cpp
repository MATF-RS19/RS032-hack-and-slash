#include "Camera.h"

#include "Character.h"

void Camera::focusOn(Character *character){
    ensureVisible(character, borderX, borderY);
}



