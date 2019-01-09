#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>
#include <QPair>
#include <QString>

class Character;
class Player;
class AnimatedItem;
class Enemy;
class Camera;
class SpellEffect;

class Map : public QGraphicsScene{
public:
    enum InputState {
        normal,
        targetCharacter,
        targetMap
    };

    Map(QString levelName);
    QPair<int, int> findPath(Character& ch, int destX, int destY);
    bool exists(int i, int j);
    void moveCharacter(Character& ch, int destX, int destY);
    QVector2D mapToScene(QVector2D worldCoords);
    QVector2D sceneToMap(QVector2D sceneCoords);
    QVector2D matrixToMap(int i, int j);
    QPair<int, int> mapToMatrix(QVector2D worldCoords);
    void setPlayer(Player* p);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void update(int deltaT);
    Player* getPlayer();
    void setCam(Camera* camera);

    void destroyEnemy(Enemy* enemy);
    void destroySpell(SpellEffect* spell);
    void addSpell(SpellEffect* spell);
    InputState getInputState();
    int getInputSpell();
    void setInputState(InputState state, int spell);
    Character* getEnemy(int i);
    int numberOfEnemies();

private:
    QVector< QVector<int> > levelCollision;
    QVector< QVector<int> > charCollision;
    QVector< QVector<int> > texMap;

    Player* player;
    QVector< Enemy* > enemies;
    QVector< SpellEffect* > spells;

    QVector< AnimatedItem* > envItems;

    InputState inputState = normal;
    int inputSpell = 0;
};

#endif // MAP_H
