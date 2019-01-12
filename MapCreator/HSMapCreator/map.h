#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>
#include <QPair>
#include <QString>

class MainWindow;

class Map : public QGraphicsScene{
public:

    Map(MainWindow* w);

    bool exists(int i, int j);

    QVector2D mapToScene(QVector2D worldCoords);
    QVector2D sceneToMap(QVector2D sceneCoords);
    QVector2D matrixToMap(int i, int j);
    QPair<int, int> mapToMatrix(QVector2D worldCoords);

    void loadMap(int width, int height);
    void loadMap(QString path);
    void saveMap(QString path);
    void clearMap();

    void setTile(int i, int j, int index);
    void setEnv(int i, int j, int index);
    void setChr(int i, int j, int index);
    void setCol(int i, int j);

    void removeEnv(int i, int j);
    void removeChr(int i, int j);

    MainWindow* getMainWindow();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:

    MainWindow* w;

    QVector< QVector<int> > col;
    QVector< QVector<int> > tex;
    QVector< QVector<int> > env;
    QVector< QVector<int> > chr;
};

#endif // MAP_H
