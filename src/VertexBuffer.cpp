#include <VertexBuffer.hpp>



    VertexBuffer::VertexBuffer(){
        glGenBuffers(1,&VBO_id);
    }

    void VertexBuffer::bindBuffer(){
         glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
    }

    void VertexBuffer::pushData(const void* data,unsigned int data_size){
        glBufferData(GL_ARRAY_BUFFER, data_size,data, GL_STATIC_DRAW);
    };

    void VertexBuffer::unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    };

    VertexBuffer::~VertexBuffer(){
        glDeleteBuffers(1,&VBO_id);
    };



