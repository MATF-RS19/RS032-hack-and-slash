#ifndef CAMERA_H
#define CAMERA_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Map;

class Camera: public QGraphicsView {
public:
    Camera(QGraphicsScene* scene) : QGraphicsView(scene) {}

    void moveCamera(int coordX, int coordY);

private:
    int cameraX, cameraY;       // pozicija kamere
    int width, height;          // velicina kvadrata u kome ce se nalaziti character

};

#endif // CAMERA_H
