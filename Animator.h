#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QPixmap>
#include <QPair>

class Animator{
public:
    Animator(){}
    Animator(QPixmap frames, int x, int y, int offsetX, int offsetY);
    Animator(QPixmap frames, int x, int y)
        : Animator(frames, x, y, (frames.width()/x)/2, frames.height()/y - 10)
    {}
    void setCurrentAnimation(int i);
    void setDefaultAnimation(int i);
    void update(int deltaT);
    QPixmap getCurrentFrame();
    void addAnimation(int start, int end, int duration, bool looping);
    int getOffsetX();
    int getOffsetY();
    bool isAnimated();

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
    int defaultAnimation;
    int offsetX, offsetY;
    QVector<Animation> animations;
};

#endif // ANIMATOR_H
