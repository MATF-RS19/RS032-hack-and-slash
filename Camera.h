#ifndef CAMERA_H
#define CAMERA_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Character;

class Camera: public QGraphicsView {
public:
    Camera(QGraphicsScene* scene, int borderX, int borderY) : QGraphicsView(scene), borderX(borderX), borderY(borderY) {}
    void focusOn(Character* character);


private:
    int borderX, borderY;
};

#endif // CAMERA_H
