
#include "Mesh.h"
#include "GL\glew.h"
#include "Vertex.h"

Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	textureID = 0;
    //WOOT 3
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        textureArray[i] = 0;
    }
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
    //WOOT 4
	//if(textureID > 0)
	//	glDeleteTextures(1, &textureID);

    //WOOT 5
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        if (textureArray[i] > 0)
        glDeleteTextures(i, &textureArray[i]);
    }
}

void Mesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	//if(textureID > 0) //WOOT 6
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	//if(mode == DRAW_LINES)
	//	glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
	//else if(mode == DRAW_TRIANGLE_STRIP)
	//	glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
	//else
	//	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
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

	//if(textureID > 0) //WOOT 7
	{
		glDisableVertexAttribArray(3);
	}
}

void Mesh::Render(unsigned offset, unsigned count)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if(textureID > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	//glDrawArrays(GL_TRIANGLES, offset, count);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	//if(mode == DRAW_LINES)
	//	glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	//else if(mode == DRAW_TRIANGLE_STRIP)
	//	glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	//else
	//	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
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

	if(textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}
}