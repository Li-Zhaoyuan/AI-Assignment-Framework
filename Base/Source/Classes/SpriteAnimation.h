#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include "Vector3.h"

struct Animation
{
    Animation() {}
    virtual ~Animation() {}

    void Set(int startFrame, int endFrame, int repeat, float time, bool active)
    {
        this->startFrame = startFrame;
        this->endFrame = endFrame;
        this->repeatCount = repeat;
        this->animTime = time;
        this->animActive = active;
    }

    int startFrame;
    int endFrame;
    int repeatCount;
    float animTime;
    bool animActive;
};

class SpriteAnimation : public Mesh
{
public:
    SpriteAnimation(const std::string &meshName, int row, int col);
    virtual ~SpriteAnimation();

    virtual void Update(double& dt);
    virtual void Render();

    int m_row;
    int m_col;

    float m_currentTime;
    int m_currentFrame;

    bool doReversal;
    bool oppositeWay;
    bool unlimitedTimes;

    Animation *m_anim;

    //bool isItBillBoard;
    //void doRotation(const Vector3 &playerPos);
    //Vector3 pos, originalPos;
    //float getRotation();

private:
    //float rotation;
};

#endif