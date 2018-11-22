#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray(const std::vector<GLfloat>& vertices, GLenum renderType) : VertexArray(vertices, empty, renderType){}

VertexArray::VertexArray(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, GLenum renderType)
{
    glGenVertexArrays(1, &ID);
    bind();
    if (indices.size() > 0)
    {
    	numIndices = indices.size();
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), renderType);
        hasEbo = true;
    }
    //  Note: when using multiple attrs in one vert array, "sizeof(vertices[0])/3" must be amended
    //  to reflect the number of attrs (3*numAttrs). EBO eliminates such convolution.
    numVertices = vertices.size() / 3;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), renderType);
}

void VertexArray::enableAttribute(int position, int sizeOfAttr, int stride, int offset)
{
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(position, sizeOfAttr, GL_FLOAT, GL_FALSE, stride * FLOAT_SIZE, (void*)(offset * FLOAT_SIZE));
    glEnableVertexAttribArray(position);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::draw()
{
	if ( hasEbo )
	{
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		//glDrawElements denotes: using the shader and vertex data we previously defined, render triangles
		//  using the number of vertices we indicated in the indices array (indices of which are type GLuint),
		//  starting at the nth index of the EBO (0th here)
	} else {
	    glDrawArrays(GL_TRIANGLES, 0, numVertices);
	    //glDrawArrays denotes: using the shader and vertex data we previously defined, render triangles
	    //  starting at index 0 of that vertex data, using the number of vertices we have in the array.
	}
}

void VertexArray::bind()
{
    glBindVertexArray(ID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
    glDeleteBuffers(1, &vbo);
    if (hasEbo) glDeleteBuffers(1, &ebo);
}
