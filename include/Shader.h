#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Shader
{
    public:
        Shader();
        ~Shader();

        bool vertexShader(const char* vertexShaderPtr);
        bool fragmentShader(const char* fragmentShaderPtr);
        bool compileShaderProgram();
        void deleteShaderProgram();
        bool useShaderProgram();
        bool deleteVertexShader();
        bool deleteFragmentShader();
        bool deleteShaders();

        unsigned int getShaderProgramID();
        //Model Matrix
        bool findModelMatrixLocation(const char* uniform_name);
        bool setModelMatrix(const float* matrix_prt);
        // View Matrix
        bool findViewMatrixLocation(const char* uniform_name);
        bool setViewMatrix(const float* matrix_prt);
        // Projection Matrix
        bool findProjMatrixLocation(const char* uniform_name);
        bool setProjMatrix(const float* matrix_prt);

    protected:

    private:
        unsigned int vertexShader_id;
        unsigned int fragmentShader_id;
        unsigned int shaderProgram_id;

        char infoLog[512]; // для записис результата проверки ошибок

        unsigned int modelLoc;
        unsigned int viewLoc;
        unsigned int projLoc;

};

#endif // SHADER_H
