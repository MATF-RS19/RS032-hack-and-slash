#ifndef CAMERA_H
#define CAMERA_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Map;
class Player;

enum PositionX{
    posinsideX,
    posleft,
    posright
};
enum PositionY{
    posinsideY,
    postop,
    posdown
};

class Camera: public QGraphicsView {
public:
    Camera(QGraphicsScene* scene, float borderX, float borderY) : QGraphicsView(scene), borderX(borderX), borderY(borderY) {}
    float getCameraX();
    float getCameraY();
    float getBorderX();
    float getBorderY();
    void setCameraX(float x);
    void setCameraY(float y);

    void update(PositionX posX, PositionY posY, float coordX, float coordY);

private:
    float cameraX, cameraY;       // pozicija kamere, ovo je gornji levi ugao (aj ges), ovo je u koordinatama mape
    float borderX, borderY;       // velicina kvadrata u kome ce se nalaziti character, ovo je u koordinatama scene

};

#endif // CAMERA_H
