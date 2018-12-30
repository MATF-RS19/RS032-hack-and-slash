#include <Animator.h>

Animator::Animator(QPixmap frames, int x, int y){
    this->frames = frames;
    dimension = QPair<int, int>(x, y);
    currentAnimation = 0;
}

void Animator::addAnimation(int start, int end, int duration, bool looping){
    Animation anim;
    anim.start = start;
    anim.end = end;
    anim.duration = duration;
    anim.current = start;
    anim.elapsed = 0;
    anim.looping = looping;

    animations.push_back(anim);
}

bool Animator::Animation::nextFrame(int deltaT){
    elapsed += deltaT;
    if(elapsed > duration){
        elapsed -= duration;
        current++;
        if(current > end)
            if(looping)
                current = start;
            else
                return false;
    }
    return true;
}

void Animator::setCurrentAnimation(int i){
    if(currentAnimation != i){
        currentAnimation = i;
        animations[i].current = animations[i].start;
        animations[i].elapsed = 0;
    }
}

void Animator::update(int deltaT){
    if(!animations[currentAnimation].nextFrame(deltaT))
        setCurrentAnimation(0);
}

QPixmap Animator::getCurrentFrame(){
    int x = animations[currentAnimation].current % dimension.first;
    int y = animations[currentAnimation].current / dimension.first;

    int width = frames.width() / dimension.first;
    int heigth = frames.height() / dimension.second;

    return frames.copy(width * x, heigth * y, width, heigth);
}
