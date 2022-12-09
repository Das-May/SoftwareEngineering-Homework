#include "game.h"

#include "resource_manager.h"
#include "Renderer.h"
#include "Camera_FPS.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Game-related State data
Renderer *test;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); 
bool firstMouse = true;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
    lastX = Game::Width / 2.0f;
    lastY = Game::Height / 2.0f;
}

Game::~Game()
{
    delete test;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "普通着色器");
    Shader s = ResourceManager::GetShader("普通着色器");
    ResourceManager::LoadTexture("textures/top.jpg", false, "棋盘格");
    Texture2D t = ResourceManager::GetTexture("棋盘格");
    s.Use().SetInteger("texture1", 0);
    ResourceManager::LoadModel("models/FPS_cube.obj", "立方体");
    Model m = ResourceManager::GetModel("立方体");

    test = new Renderer(ResourceManager::LoadModel("models/FPS_cube.obj", "立方体"), s, t);
}

void Game::Update(float dt)
{
    ResourceManager::GetShader("普通着色器").Use().SetMatrix4("view", camera.GetViewMatrix());
    glm::mat4 projection = glm::perspective(45.0f, (float)Width / (float)Height, 0.1f, 100.0f);
    // 我也不知道为什么正交投影会无法显示
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("普通着色器").SetMatrix4("projection", projection);
}

void Game::ProcessInput(float dt)
{
    // 处理键盘输入
    if (this->Keys[GLFW_KEY_W] == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (this->Keys[GLFW_KEY_S] == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (this->Keys[GLFW_KEY_A] == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (this->Keys[GLFW_KEY_D] == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);

    // 处理鼠标输入
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
    test->Draw();
}