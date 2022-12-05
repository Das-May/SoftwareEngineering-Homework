/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#define GLEW_STATIC
#include <GL/glew.h>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"
#include "model.h"




// GLFW function declerations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    // glfw: 初始化和配置
    // ---------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // 禁止调整窗口大小
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw 窗口创建
    // ---------------------------------------
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FPS Game Engine", nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glfw 加入设备输入操作
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glew库 配置
    glewExperimental = GL_TRUE; // 令glew在初始化期间试图加载OpenGL的所有拓展函数
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    

    // glad: 加载所有OpenGL函数指针
    // ---------------------------------------
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }*/

    // OpenGL 配置
    // ---------------------------------------
    //glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //glEnable(GL_CULL_FACE);             //开启背面剔除
    //glEnable(GL_BLEND);                 //开启混合
    //glEnable(GL_DEPTH_TEST);            //开启深度测试

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 初始化游戏
    Breakout.Init();
    //Model m = Model("models/FPS_box.obj");
    //m.Draw(ResourceManager::GetShader("天空盒"));

    

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // Start Game within Menu State
    Breakout.State = GAME_ACTIVE;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        //deltaTime = 0.001f;
        // Manage user input
        Breakout.ProcessInput(deltaTime);

        // Update Game state
        Breakout.Update(deltaTime);

        // Render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);// 在渲染新一帧时清除深度缓存
        Breakout.Render();

        glfwSwapBuffers(window);
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            Breakout.Keys[key] = GL_FALSE;
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    Breakout.xposIn = xposIn;
    Breakout.yposIn = yposIn;
}