#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
//#include <iostream>

// GUI imgui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <font_arial.hpp>


#include <constants.h>
#include <shaders.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <gl_utils.h>
#include <VertexBuffer.hpp>
#include <VertexArrayObject.h>
#include <Shader.h>

int main()
{
    GLFWwindow* window=OpenGlInit(SCR_WIDTH,SCR_HEIGHT,"Lab2"); // GlUtils
    if (window==nullptr){
        return -1;
    }
    /**************************************/
    // создать массив точек и цветов
    // у фигуры всего 7 точек, для построения 10 треугольников с разными цветами
    float points[10][3][6]; // 10 треугольников по 3 точки по 6 компонент на точку
    for (int i=0;i<10;++i){ // для каждого треугольника
        for (int j=0;j<3;++j){ // для каждой из трех точек
                for (int k=0;k<3;++k){ // для каждой из трех компонент позиции и цвета
                   points[i][j][k]=piramid[indices[i][j]][k]; // компоненты позиции
                   points[i][j][k+3]=colors[i][k]; // компоненты цвета
                }
        }
    }

    /***************************************************************/
    // создать буфер для точек (vertex bufer)
    VertexBuffer* vbo=new VertexBuffer();
    vbo->bindBuffer();
    vbo->pushData(static_cast<void*>(points),sizeof(points));
    // Vertex Array Object
    VertexArrayObject* vao=new VertexArrayObject();
    vao->bindBuffer();

    // аттрибуты данных, арггументы:  индекс аттрибута, количество аттрибутов, тип аттрибута
    // необходимость нормализации = false, смещение между наборами аттрибутов , смещение до первого аттрибута
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // координаты
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float)*3)); // цвета
    glEnableVertexAttribArray(1);

    /********************************************************************/
    // матрицы трансформаций
    glm::mat4 model_matrix=glm::mat4(1.0f); // матрица модели - поворота на 90 градусов вокруг оси Х
    model_matrix=glm::rotate(model_matrix, glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
    glm::mat4 view_matrix;   // матрица вида
     // аргументы - позиция камеры, позиция фокуса,вектор вверх в мировых координатах
    view_matrix = glm::lookAt(glm::vec3(0, 0,8.0f ),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 1.0f));
    // матрица проекции - угол обзора, соотношение сторон, ближняя и дальняя проекционная плоскость
    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    /********************************************************************/
    Shader* shaderObj=new Shader();
    shaderObj->vertexShader(vertexShaderSource);
    shaderObj->fragmentShader(fragmentShaderSource);
    shaderObj->compileShaderProgram();
    shaderObj->useShaderProgram();
    shaderObj->deleteShaders();
    shaderObj->findModelMatrixLocation("model_matr");
    shaderObj->setModelMatrix(glm::value_ptr(model_matrix));
    shaderObj->findViewMatrixLocation("view_matr");
    shaderObj->findProjMatrixLocation("proj_matr");
    shaderObj->setProjMatrix(glm::value_ptr(projection_matrix));

    glEnable(GL_DEPTH_TEST); // тестирование буфера глубины
    glPolygonMode(GL_FRONT, GL_FILL);
    /********************************************************************/
    // создать интерфейс
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io=ImGui::GetIO();(void)io;
    //io.Fonts->AddFontFromFileTTF("fonts/arial.ttf",10,NULL,io.Fonts->GetGlyphRangesCyrillic());// добавить кириллицу
    io.Fonts->AddFontFromMemoryCompressedTTF(ArialFont_compressed_data,ArialFont_compressed_size,10.0f,NULL,io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");
    float cameraz{7.0f},cameray{4.0f},camerax{4.0f};
    float lastTime{0.0f},now{0.0f};
    float speedA{70.0f};
     /********************************************************************/
    // Главный цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);
		// Выполнение рендеринга
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //gui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Матрицы");
        ImGui::SliderFloat("Камера Z", &cameraz, 0.0f, 50.0f);
        ImGui::SliderFloat("Камера X", &camerax, 0.0f, 20.0f);
        ImGui::SliderFloat("Камера Y", &cameray, 0.0f, 20.0f);
        ImGui::SliderFloat("Скорость А", &speedA, 0.0f, 1000.0f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        view_matrix = glm::lookAt(glm::vec3(camerax, cameray,cameraz),glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        shaderObj->setViewMatrix(glm::value_ptr(view_matrix));

        now=glfwGetTime();
        model_matrix=glm::rotate(model_matrix, glm::radians((now-lastTime)*speedA), glm::vec3(0.0, 0.0,1.0));
        shaderObj->setModelMatrix(glm::value_ptr(model_matrix));
        glDrawArrays(GL_TRIANGLES, 0, 30);
        lastTime=now;

        // glfw: обмен содержимым front- и back-буферов. Отслеживание событий ввода/вывода
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    shaderObj->compileShaderProgram();

    // завершить выполнени gui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
    return 0;
}


