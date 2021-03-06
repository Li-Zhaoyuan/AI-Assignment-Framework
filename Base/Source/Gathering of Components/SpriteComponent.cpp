#include "SpriteComponent.h"
#include "GL\glew.h"
#include "../Classes/Vertex.h"
#include "AnimationComponent.h"

SpriteComponent::SpriteComponent()
{
    SpriteComponent("nothing", 1, 1);
}

SpriteComponent::SpriteComponent(const std::string &zeName, const size_t &zeRow, const size_t &zeCol)
{
    name_ = zeName;
    //zeAnimTime = nullptr;
    m_col = zeCol;
    m_row = zeRow;
    m_currentFrame = 0;
}

SpriteComponent::~SpriteComponent()
{
    //zeAnimTime = nullptr;
}

void SpriteComponent::Render()
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

bool SpriteComponent::onNotify(GenericComponent &zeEvent)
{
    //zeAnimTime = &zeEvent;
    AnimationComponent * zeAnim = dynamic_cast<AnimationComponent*>(&zeEvent);
    //int numFrame = 0;
    //numFrame = Math::Max(zeAnim->startFrame + 1, zeAnim->endFrame - zeAnim->startFrame + 1);
    //float frameTime = 0;
    //frameTime = (zeAnim->animTime / static_cast<float>(numFrame));

    m_currentFrame = Math::Min(zeAnim->endFrame, zeAnim->startFrame + static_cast<int>(zeAnim->m_currentTime / zeAnim->frameTime));
    return true;
}