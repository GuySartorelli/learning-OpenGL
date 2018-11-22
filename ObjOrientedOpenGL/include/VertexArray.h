#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#define FLOAT_SIZE sizeof(GLfloat)

#include <glad/glad.h>
#include <string>
#include <vector>

class VertexArray
{
    public:
		VertexArray(const std::vector<GLfloat>&, GLenum);
		VertexArray(const std::vector<GLfloat>&, const std::vector<GLuint>&, GLenum);
        void enableAttribute(int, int, int, int);
        void draw();
        void bind();
        void unbind();
        ~VertexArray();
    protected:
    private:
        GLuint ID;
        GLuint vbo;
        GLuint ebo;
        int numIndices = 0;
        int numVertices = 0;
        bool hasEbo = false;
        std::vector<GLuint> empty = std::vector<GLuint>();
};

#endif // VERTEXARRAY_H
