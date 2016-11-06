#include "MyMeshComponent.h"
#include "GL\glew.h"
#include "../Classes\Vertex.h"

MyMeshComponent::MyMeshComponent()
: MyMeshComponent("", nullptr)
{

}

MyMeshComponent::MyMeshComponent(const std::string &zeName, GenericEntity *zeOwner)
{
    GenericComponent(zeName, zeOwner);
    mode = DRAW_TRIANGLES;
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);
    //textureID = 0;

    //init texture array to 0
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        textureArray[i] = 0;
    }
}

MyMeshComponent::~MyMeshComponent()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);

    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        glDeleteTextures(1, &textureArray[i]);
    }
}

void MyMeshComponent::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));
    //if(textureID > 0)
    {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)+sizeof(Vector3)));
    }


    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    switch (mode)
    {
    case DRAW_LINES:
        glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
        break;
    case DRAW_TRIANGLE_STRIP:
        glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
        break;
    default:
        glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    //if(textureID > 0)
    {
        glDisableVertexAttribArray(3);
    }
}

void MyMeshComponent::Render(unsigned offset, unsigned count)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));
    //if (textureID > 0)
    {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)+sizeof(Vector3)));
    }

    //glDrawArrays(GL_TRIANGLES, offset, count);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    switch (mode)
    {
    case DRAW_LINES:
        glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
        break;
    case DRAW_TRIANGLE_STRIP:
        glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
        break;
    default:
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
        break;
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    //if (textureID > 0)
    {
        glDisableVertexAttribArray(3);
    }
}