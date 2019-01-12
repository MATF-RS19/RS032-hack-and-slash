#include "Map.h"

#include <QQueue>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QFile>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QList>

#include <cmath>

#include "mapitem.h"
#include "mainwindow.h"

Map::Map(MainWindow* w){
    this->w = w;
}

void Map::loadMap(int width, int height) {
    clearMap();
    for(int i = 0; i < width; i++) {
        QVector<int> colRow;
        QVector<int> texRow;
        QVector<int> envRow;
        QVector<int> chrRow;
        for(int j = 0; j < height; j++) {
            colRow.push_back(0);
            texRow.push_back(0);
            envRow.push_back(0);
            chrRow.push_back(0);
            addRect(mapToScene(matrixToMap(i, j)).x() - 2, mapToScene(matrixToMap(i, j)).y() - 2, 4, 4)->setBrush(Qt::white);
            addItem(new MapItem(w->getPixmap(MapItem::Type::tile, 0), this, i, j, MapItem::Type::tile));
        }
        col.push_back(colRow);
        tex.push_back(texRow);
        env.push_back(envRow);
        chr.push_back(chrRow);
    }
}

void Map::loadMap(QString path) {
    clearMap();

    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);


    QString line = file.readLine();
    QStringList list = line.split(" ");
    int n = list.at(0).toInt();
    int m = list.at(1).toInt();

    col = QVector< QVector<int> > (m);
    tex = QVector< QVector<int> > (m);
    env = QVector< QVector<int> > (m);
    chr = QVector< QVector<int> > (m);

    for(int i = 0; i < m; i++){
        col[i] = QVector<int>();
        tex[i] = QVector<int>();
        env[i] = QVector<int>();
        chr[i] = QVector<int>();
        QString line = file.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            int x = list.at(j).toInt();
            col[i].push_back(x);
            chr[i].push_back(0);
            addRect(mapToScene(matrixToMap(i, j)).x() - 2, mapToScene(matrixToMap(i, j)).y() - 2, 4, 4)->setBrush(Qt::white);
        }
    }

    qDebug() << col;

    for(int i = 0; i < m; i++){
        QString line = file.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            int x = list.at(j).toInt();
            tex[i].push_back(x);
            addItem(new MapItem(w->getPixmap(MapItem::Type::tile, x), this, i, j, MapItem::Type::tile));
        }
    }

    for(int i = 0; i < m; i++){
        QString line = file.readLine();
        QStringList list = line.split(" ");
        for(int j = 0; j < n; j++){
            int x = list.at(j).toInt();
            env[i].push_back(x);
            if(x)
                addItem(new MapItem(w->getPixmap(MapItem::Type::env, x - 1), this, i, j, MapItem::Type::env));
        }
    }

    line = file.readLine().trimmed();
    int s = line.toInt();

    for(int i = 0; i < s; i++){
        line = file.readLine().trimmed();
        list = line.split(" ");
        int x = list.at(0).toInt();
        int mi = list.at(1).toInt();
        int mj = list.at(2).toInt();
        chr[mj][mi] = x;
        /*chr[i].push_back(mi);
        chr[i].push_back(mj);
        for(int j = 3; j < list.size(); j++) {
            int y = list.at(j).toInt();
            chr[i].push_back(y);
        }*/
        if(x > 1)
            addItem(new MapItem(w->getPixmap(MapItem::Type::chr, x - 1), this, mj, mi, MapItem::Type::chr));
    }


}

void Map::saveMap(QString path) {
    QFile file( path );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << col[0].size() << " " << col.size() << endl;
        for(int i = 0; i < col.size(); i++) {
            for(int j = 0; j < col[i].size(); j++)
                stream << col[i][j] << " ";
            stream << endl;
        }
        for(int i = 0; i < col.size(); i++) {
            for(int j = 0; j < col[i].size(); j++)
                stream << tex[i][j] << " ";
            stream << endl;
        }
        for(int i = 0; i < col.size(); i++) {
            for(int j = 0; j < col[i].size(); j++)
                stream << env[i][j] << " ";
            stream << endl;
        }
        int cc = 0;
        for(int i = 0; i < col.size(); i++) {
            for(int j = 0; j < col[i].size(); j++)
                cc += (bool) chr[i][j];
        }
        stream << cc << endl;
        for(int i = 0; i < col.size(); i++) {
            for(int j = 0; j < col[i].size(); j++)
                if(chr[i][j])
                    stream << chr[i][j] << " " << i << " " << j << endl;
        }

    }
}

void Map::clearMap() {
    col.clear();
    env.clear();
    chr.clear();
    tex.clear();
    clear();
}

MainWindow* Map::getMainWindow() {
    return w;
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent* event) {

    QGraphicsScene::mousePressEvent(event);
}

void Map::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key::Key_W:
        //this->
        break;
    }

    QGraphicsScene::keyPressEvent(event);
}

QVector2D Map::mapToScene(QVector2D worldCoords){
    QVector2D cameraPos = QVector2D(1.5, 1.5);
    QVector2D sceneCenter = QVector2D(150, 150);

    QVector2D translate = worldCoords - cameraPos;

    float x = (translate.x() - translate.y())/sqrt(2);
    float y = 0.5 * (translate.x() + translate.y())/sqrt(2);
    QVector2D vektor = QVector2D(x, y);

    vektor *= 50;

    return  vektor + sceneCenter;
}

QVector2D Map::sceneToMap(QVector2D sceneCoords){
    QVector2D cameraPos = QVector2D(1.5, 1.5);
    QVector2D sceneCenter = QVector2D(150, 150);

    QVector2D translate = sceneCoords - sceneCenter;

    float x = (translate.x() + 2 * translate.y())/sqrt(2);
    float y = (2 * translate.y() - translate.x())/sqrt(2);

    QVector2D vektor = QVector2D(x, y);

    vektor *= 0.02;

    return vektor + cameraPos;
}

QVector2D Map::matrixToMap(int i, int j){
    return QVector2D(j + 0.5, i + 0.5);
}

QPair<int, int> Map::mapToMatrix(QVector2D worldCoords){
    return QPair<int, int>(worldCoords.y() - 0.5, worldCoords.x() - 0.5);
}

bool Map::exists(int i, int j){
    return i >= 0 && j >= 0 && i < col.size() && j < col[i].size();
}

void Map::setTile(int i, int j, int index) {
    if(exists(i, j)) {
        tex[i][j] = index;
        addItem(new MapItem(w->getPixmap(MapItem::tile, index), this, i, j, MapItem::tile));
    }
}

void Map::setEnv(int i, int j, int index) {
    if(exists(i, j) && env[i][j] == 0 && chr[i][j] == 0) {
        env[i][j] = index + 1;
        addItem(new MapItem(w->getPixmap(MapItem::env, index), this, i, j, MapItem::env));
    }
}

void Map::setChr(int i, int j, int index) {
    qDebug() << "yaas";
    qDebug() << i << j << index;
    qDebug() << env << chr << col;
    if(exists(i, j) && env[i][j] == 0 && chr[i][j] == 0 && col[i][j] == 0) {
        chr[i][j] = index;
        addItem(new MapItem(w->getPixmap(MapItem::chr, index), this, i, j, MapItem::chr));
    }
}

void Map::setCol(int i, int j) {
    if(exists(i, j))
        col[i][j] = !col[i][j];

    addRect(mapToScene(matrixToMap(i, j)).x() - 2, mapToScene(matrixToMap(i, j)).y() - 2, 4, 4)->setBrush(col[i][j] ? Qt::black : Qt::white);
}

void Map::removeEnv(int i, int j) {
    if(exists(i, j))
        env[i][j] = 0;
}

void Map::removeChr(int i, int j) {
    if(exists(i, j))
        chr[i][j] = 0;
}
