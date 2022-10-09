#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

 const char * const vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 outCol;\n"
    "uniform mat4 model_matr;\n"
    "uniform mat4 view_matr;\n"
    "uniform mat4 proj_matr;\n"
    "void main()\n"
    "{\n"
       "gl_Position =proj_matr*view_matr*model_matr*vec4(aPos.x,aPos.y,aPos.z,1);\n"
        "outCol=aCol;\n"
    "}\0";

 const char * const fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 outCol;\n"
    "uniform vec4 col;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outCol,1.0);\n"
    "}\n\0";



#endif // SHADERS_H_INCLUDED
