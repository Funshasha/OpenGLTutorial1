//
//  main.cpp
//  CG1
//
//  Created by rui huang on 2022/9/13.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#define ERRORLOG(message) std::cout << message << std::endl;glfwTerminate();return -1;
/*

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0f);\n"
"}";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);\n"
"}";

static void CreateShaderProgram(GLuint shaderProgram)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "ERROR::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
#ifndef __APPLE__
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::VALIDATE_FAILED\n" << infoLog << std::endl;
    }
#endif // !__APPLE__
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
*/
GLuint VAO, VBO;
static void CreateVertexBuffer()
{
    /*
    GLfloat vertices[] = { -0.5f, -1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f,
                          0.5f, -1.0f, 0.0f };//{ 0.0f, 0.0f, 0.0f };
    */
    GLfloat vertices[] = {
                           //¸¡µã               ÑÕÉ«
                                  //first
                          1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
                          0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f,
                          0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
                                 //second
                          0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f,
                          1.0f, 0.0f, 0.5f,  1.0f, 0.0f, 1.0f,
                          1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 
                                 //three
                          -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                          -0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
                          0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
static void SetViewport(GLFWwindow* window)
{
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth,
        &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
}
static void RenderScreen(GLFWwindow* window)
{
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    //glDrawArrays(GL_POINTS, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
}
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Tutorial 1", NULL, NULL);
    if (window == NULL) { ERRORLOG("Failed to create Window!") }
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit()) { ERRORLOG("Failed to init GLEW!") }
    CreateVertexBuffer();
    Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.fs");
 // GLuint ShaderProgram = glCreateProgram();
 // CreateShaderProgram(ShaderProgram);
    while (!glfwWindowShouldClose(window))
    {
        SetViewport(window);
        glfwPollEvents();
 //     glUseProgram(ShaderProgram);
        shader.UseProgram();
        RenderScreen(window);
    }
    glfwTerminate();
    return 1;
}
