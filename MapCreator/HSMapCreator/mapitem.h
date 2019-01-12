#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>

class Map;

class MapItem: public QGraphicsPixmapItem {
public:
    enum Type {
        tile,
        env,
        chr
    };

    MapItem(QPixmap pixmap, Map* m, int matI, int matJ, Type type);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    Map* m;

    int matI, matJ;
    Type type;
};

#endif // MAPITEM_H
