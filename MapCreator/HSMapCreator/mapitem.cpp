#include "mapitem.h"

#include <QGraphicsSceneMouseEvent>
#include "mainwindow.h"
#include "map.h"

MapItem::MapItem(QPixmap pixmap, Map* m, int matI, int matJ, Type type):
    QGraphicsPixmapItem (pixmap), m(m), matI(matI), matJ(matJ), type(type)
{
    QVector2D viewPos = m->mapToScene(m->matrixToMap(matI, matJ));
    setPos(viewPos.x(), viewPos.y());

    switch(type) {
    case tile:
        setZValue(-1);
        setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
        break;
    case env:
        setZValue(matI + matJ);
        setOffset(-pixmap.width() / 2, -pixmap.height() * 0.8);
        break;
    case chr:
        setZValue(matI + matJ);
        setOffset(-pixmap.width() / 2, -pixmap.height() * 0.6);
    }
}

void MapItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(event->button() == Qt::MouseButton::LeftButton) {
        if(type == tile) {
            switch(m->getMainWindow()->getMode()){
            case 0:
                m->setTile(matI, matJ, m->getMainWindow()->getAssetIdx());
                delete this;
                break;
            case 1:
                m->setEnv(matI, matJ, m->getMainWindow()->getAssetIdx());
                break;
            case 2:
                m->setChr(matI, matJ, m->getMainWindow()->getAssetIdx());
                break;
            }
        }
    }
    else if(event->button() == Qt::MouseButton::RightButton) {
        switch(type) {
        case tile:
            m->setCol(matI, matJ);
            break;
        case env:
            m->removeEnv(matI, matJ);
            delete this;
            break;
        case chr:
            m->removeChr(matI, matJ);
            delete this;
            break;
        }
    }
}
