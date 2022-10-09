#ifndef VERTEXBUFFER_HPP_INCLUDED
#define VERTEXBUFFER_HPP_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer{
    public:
    VertexBuffer();

    void bindBuffer();

    void pushData(const void* data,unsigned int data_size);

    void unbind();

    ~VertexBuffer();

    private:
    unsigned int VBO_id;
};

#endif // VERTEXBUFFER_HPP_INCLUDED
