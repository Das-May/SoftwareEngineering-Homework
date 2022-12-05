/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "model.h"
#include "Camera_FPS.h"


// Game-related State data
SpriteRenderer* Renderer;
Model* Skybox;

// camera
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;


Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
    //ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "天空盒");
    
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    /*for (auto& shader : ResourceManager::Shaders)
    {
        shader.second.SetMatrix4("projection", projection);
    }
    glm::mat4 view = camera.GetViewMatrix();
    ResourceManager::GetShader("天空盒").SetMatrix4("view", view);*/

    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    
    // Load textures
    ResourceManager::LoadTexture("textures/crosshair.png", GL_TRUE, "准星");

    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    //Skybox = new Model("models/FPS_cube.obj");
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{
    // 处理键盘输入
    if (this->State == GAME_ACTIVE)
    {
        /*if (this->Keys[GLFW_KEY_ESCAPE])
            glfwSetWindowShouldClose(window, true);*/

        if (this->Keys[GLFW_KEY_W])
            camera.ProcessKeyboard(FORWARD, dt);
        if (this->Keys[GLFW_KEY_S])
            camera.ProcessKeyboard(BACKWARD, dt);
        if (this->Keys[GLFW_KEY_A])
            camera.ProcessKeyboard(LEFT, dt);
        if (this->Keys[GLFW_KEY_D])
            camera.ProcessKeyboard(RIGHT, dt); 
    }
    
    // 处理鼠标输入
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("准星"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    //Skybox->Draw(ResourceManager::GetShader("天空盒"));
}