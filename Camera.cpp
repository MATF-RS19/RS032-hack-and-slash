#include "Camera.h"

float Camera::getCameraX(){
    return cameraX;
}


float Camera::getCameraY(){
    return cameraY;
}

float Camera::getBorderX(){
    return borderX;
}

float Camera::getBorderY(){
    return borderY;
}

void Camera::setCameraX(float x){
    cameraX = x;
}

void Camera::setCameraY(float y){
    cameraY = y;
}

void Camera::update(PositionX posX, PositionY posY, float coordX, float coordY){
    if(posX != posinsideX || posY != posinsideY)
        centerOn(coordX, coordY);
}



