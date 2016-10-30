#include "SpriteAnimation.h"
#include "GL\glew.h"
#include "Vertex.h"
#include "MyMath.h"

SpriteAnimation::SpriteAnimation(const std::string &meshName, int row, int col)
    : Mesh(meshName), m_row(row), m_col(col), m_currentFrame(0), m_currentTime(0),
    m_anim(NULL), doReversal(false), /*rotation(0), isItBillBoard(false),*/ oppositeWay(false),
    unlimitedTimes(false)
{

}


SpriteAnimation::~SpriteAnimation()
{
    if (m_anim)
        delete m_anim;
}

void SpriteAnimation::Update(double &dt)
{
    if (m_anim->animActive == true)
    {
        m_currentTime += (float)dt;

        int numFrame = 0;
        if (m_anim->startFrame <= m_anim->endFrame)
        {
            numFrame = Math::Max(m_anim->startFrame + 1, m_anim->endFrame - m_anim->startFrame + 1);
        }
        //this is for animation to play backwards
        else
        {
            numFrame = Math::Max(m_anim->endFrame + 1, m_anim->startFrame - m_anim->endFrame + 1);
        }

        float frameTime = 0;
        frameTime = (m_anim->animTime / static_cast<float>(numFrame));

        if (oppositeWay)
        {
            m_currentFrame = Math::Max(m_anim->startFrame, m_anim->endFrame - static_cast<int>(m_currentTime / frameTime));
        }
        else
        {
            if (m_anim->startFrame <= m_anim->endFrame)
                m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + static_cast<int>(m_currentTime / frameTime));
            else         //this is for animation to play backwards
                m_currentFrame = Math::Min(m_anim->startFrame, m_anim->endFrame + static_cast<int>(m_currentTime / frameTime));
        }

        if (m_currentTime >= m_anim->animTime)
        {
            if (unlimitedTimes == false && m_anim->repeatCount <= 0)
            {
                m_anim->animActive = false;
                m_currentTime = 0.f;
            }
            else
            {
                m_currentTime = 0.f;
                if (unlimitedTimes == false)
                    --m_anim->repeatCount;
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
                if (oppositeWay)
                    m_currentFrame = m_anim->endFrame;
                else
                    m_currentFrame = m_anim->startFrame;
            }
        }
    }
    else if (m_anim->repeatCount > 0 || unlimitedTimes == true)
    {
        m_currentTime = 0.f;
        m_anim->animActive = true;
        if (unlimitedTimes == false)
            --m_anim->repeatCount;
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
        if (oppositeWay)
            m_currentFrame = m_anim->endFrame;
        else
            m_currentFrame = m_anim->startFrame;
    }
}

void SpriteAnimation::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
    {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    //if (mode == DRAW_LINES)
    //    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
    //else if (mode == DRAW_TRIANGLE_STRIP)
    //    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
    //else
    //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
    switch (mode)
    {
    case DRAW_LINES:
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
        break;
    case DRAW_TRIANGLE_STRIP:
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
        break;
    default:
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    {
        glDisableVertexAttribArray(3);
    }
}

//void SpriteAnimation::doRotation(const Vector3 &playerPos)
//{
//    Vector3 tempView = (pos - playerPos);
//    tempView.y = 0;
//    tempView.Normalize();
//    rotation = Math::RadianToDegree(atan2(-tempView.z, tempView.x));
//}
//
//float SpriteAnimation::getRotation()
//{
//    return rotation;
//}