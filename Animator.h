#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QPixmap>
#include <QPair>

class Animator{
public:
    Animator(){}
    Animator(QPixmap frames, int x, int y);
    void setCurrentAnimation(int i);
    void update(int deltaT);
    QPixmap getCurrentFrame();
    void addAnimation(int start, int end, int duration, bool looping);

private:
    QPixmap frames;
    QPair<int, int> dimension;

    class Animation{
    public:
        bool nextFrame(int deltaT);
        int start, current, end;
        int duration;
        int elapsed;
        bool looping;
    };
    int currentAnimation;

    QVector<Animation> animations;
};

#endif // ANIMATOR_H
