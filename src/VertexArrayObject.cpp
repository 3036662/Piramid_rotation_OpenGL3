#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
     glGenVertexArrays(1, &VAO_id);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1,&VAO_id);
}


void VertexArrayObject::bindBuffer(){
    glBindVertexArray(VAO_id);
}
