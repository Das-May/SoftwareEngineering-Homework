#include "game.h"

#include "resource_manager.h"
#include "Renderer.h"
#include "Camera_FPS.h"
#include "game_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// 用户参数
Parameter parameter;

// Game-related State data
Renderer* test;
Renderer* scene;
Renderer* cube;
Renderer* enemy;

vector<GameObject*> enemies;
vector<GameObject*> bags;
vector<GameObject*> Obstacles;

// 摄像机
Camera camera(glm::vec3(0.0f, 1.5f, 3.0f)); 
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
    // 加载用户参数
    parameter = ResourceManager::LoadParameter();

    // 加载着色器
    ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "普通着色器");

    // 配置着色器
    Shader s;
    s = ResourceManager::GetShader("普通着色器");
    s.Use();
    s.SetInteger("texture1", 0);

    // 加载纹理
    ResourceManager::LoadTexture("textures/CheckerboardLattice.jpg", false, "棋盘格");
    ResourceManager::LoadTexture("textures/box/XZ_XiangGai_BaseColor.png", false, "箱子_基本贴图");
    ResourceManager::LoadTexture("textures/cannon/Sentry_Turret_ALL_02_-_Default_BaseColor.png", false, "炮台_基本贴图");

    // 加载模型
    ResourceManager::LoadModel("models/cube.obj", "立方体");
    ResourceManager::LoadModel("models/FPS_box.obj", "场景");
    ResourceManager::LoadModel("models/box.obj", "箱子");
    ResourceManager::LoadModel("models/cannon.obj", "炮台");

    // 创建游戏对象
    for (int i = 0; i < parameter.bag_parameter.size(); i++)
    {
        CharacterParameter bag = parameter.bag_parameter[i];
        bags.push_back(new GameObject(BAG, glm::vec2(bag.x, bag.z), 0.01, bag.hp, bag.atk));
    }
    
 /*   test = new Renderer(ResourceManager::GetModel("立方体"), 
        ResourceManager::GetShader("天空盒着色器"), 
        ResourceManager::GetTexture("天空盒"));*/
    

    // 创建渲染对象
    cube = new Renderer(ResourceManager::GetModel("箱子"), 
        ResourceManager::GetShader("普通着色器"),
        ResourceManager::GetTexture("箱子_基本贴图"));
    scene = new Renderer(ResourceManager::GetModel("场景"),
        s,
        ResourceManager::GetTexture("棋盘格"));
    /*enemy = new Renderer(ResourceManager::GetModel("炮台"),
        s,
        ResourceManager::GetTexture("炮台_基本贴图"));*/
}

void Game::Update(float dt)
{
    ResourceManager::GetShader("普通着色器").Use().SetMatrix4("view", camera.GetViewMatrix());
    glm::mat4 projection = glm::perspective(45.0f, (float)Width / (float)Height, 0.1f, 100.0f);
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
    //test->Draw();
    scene->Draw(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(parameter.scene_parameter.width,  1.0f, parameter.scene_parameter.length));
    for (auto& bag : bags)
        bag->Draw(*cube);
    //cube->Draw();
    //enemy->Draw();
}