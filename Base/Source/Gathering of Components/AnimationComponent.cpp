#include "AnimationComponent.h"
#include "MyMath.h"

AnimationComponent::AnimationComponent()
{
    m_currentTime = 0;
    doReversal = false;
    oppositeWay = false;
    unlimitedTimes = false;
    frameTime = 0;
    numFrame = 0;
}
AnimationComponent::~AnimationComponent() 
{

}

void AnimationComponent::Update(double dt)
{
    if (animActive == true)
    {
        m_currentTime += (float)dt;

        if (startFrame <= endFrame)
        {
            numFrame = Math::Max(startFrame + 1, endFrame - startFrame + 1);
        }
        //this is for animation to play backwards
        else
        {
            numFrame = Math::Max(endFrame + 1, startFrame - endFrame + 1);
        }

        frameTime = (animTime / static_cast<float>(numFrame));

        //if (oppositeWay)
        //{
        //    m_currentFrame = Math::Max(m_anim->startFrame, m_anim->endFrame - static_cast<int>(m_anim->m_currentTime / frameTime));
        //}
        //else
        //{
        //    if (m_anim->startFrame <= m_anim->endFrame)
        //        m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + static_cast<int>(m_anim->m_currentTime / frameTime));
        //    else         //this is for animation to play backwards
        //        m_currentFrame = Math::Min(m_anim->startFrame, m_anim->endFrame + static_cast<int>(m_anim->m_currentTime / frameTime));
        //}

        if (m_currentTime >= animTime)
        {
            if (unlimitedTimes == false && repeatCount <= 0)
            {
                animActive = false;
                m_currentTime = 0.f;
            }
            else
            {
               m_currentTime = 0.f;
                if (unlimitedTimes == false)
                    --repeatCount;
                if (doReversal)
                {
                    if (oppositeWay)
                    {
                        oppositeWay = false;
                    }
                    else
                    {
                        oppositeWay = true;
                    }
                }
                //if (oppositeWay)
                //    m_currentFrame = m_anim->endFrame;
                //else
                //    m_currentFrame = m_anim->startFrame;
            }
        }
    }
    else if (repeatCount > 0 || unlimitedTimes == true)
    {
        m_currentTime = 0.f;
        animActive = true;
        if (unlimitedTimes == false)
            --repeatCount;
        if (doReversal)
        {
            if (oppositeWay)
            {
                oppositeWay = false;
            }
            else
            {
                oppositeWay = true;
            }
        }
        //if (oppositeWay)
        //    m_currentFrame = m_anim->endFrame;
        //else
        //    m_currentFrame = m_anim->startFrame;
    }
}