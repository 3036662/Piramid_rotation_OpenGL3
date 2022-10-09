#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexArrayObject
{
    public:
        VertexArrayObject();
        ~VertexArrayObject();

        void bindBuffer();

    protected:

    private:
        unsigned int VAO_id;
};

#endif // VERTEXARRAYOBJECT_H
