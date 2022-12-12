#include "game.h"

#include "resource_manager.h"
#include "Renderer.h"
#include "Camera_FPS.h"
#include "game_object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// �û�����
Parameter parameter;

// Game-related State data
Renderer* test;
Renderer* scene;
Renderer* cube;
Renderer* enemy;

vector<GameObject*> enemies;
vector<GameObject*> bags;
vector<GameObject*> Obstacles;

// �����
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
    // �����û�����
    parameter = ResourceManager::LoadParameter();

    // ������ɫ��
    ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "��ͨ��ɫ��");

    // ������ɫ��
    Shader s;
    s = ResourceManager::GetShader("��ͨ��ɫ��");
    s.Use();
    s.SetInteger("texture1", 0);

    // ��������
    ResourceManager::LoadTexture("textures/CheckerboardLattice.jpg", false, "���̸�");
    ResourceManager::LoadTexture("textures/box/XZ_XiangGai_BaseColor.png", false, "����_������ͼ");
    ResourceManager::LoadTexture("textures/cannon/Sentry_Turret_ALL_02_-_Default_BaseColor.png", false, "��̨_������ͼ");

    // ����ģ��
    ResourceManager::LoadModel("models/cube.obj", "������");
    ResourceManager::LoadModel("models/FPS_box.obj", "����");
    ResourceManager::LoadModel("models/box.obj", "����");
    ResourceManager::LoadModel("models/cannon.obj", "��̨");

    // ������Ϸ����
    for (int i = 0; i < parameter.bag_parameter.size(); i++)
    {
        CharacterParameter bag = parameter.bag_parameter[i];
        bags.push_back(new GameObject(BAG, glm::vec2(bag.x, bag.z), 0.01, bag.hp, bag.atk));
    }
    
 /*   test = new Renderer(ResourceManager::GetModel("������"), 
        ResourceManager::GetShader("��պ���ɫ��"), 
        ResourceManager::GetTexture("��պ�"));*/
    

    // ������Ⱦ����
    cube = new Renderer(ResourceManager::GetModel("����"), 
        ResourceManager::GetShader("��ͨ��ɫ��"),
        ResourceManager::GetTexture("����_������ͼ"));
    scene = new Renderer(ResourceManager::GetModel("����"),
        s,
        ResourceManager::GetTexture("���̸�"));
    /*enemy = new Renderer(ResourceManager::GetModel("��̨"),
        s,
        ResourceManager::GetTexture("��̨_������ͼ"));*/
}

void Game::Update(float dt)
{
    ResourceManager::GetShader("��ͨ��ɫ��").Use().SetMatrix4("view", camera.GetViewMatrix());
    glm::mat4 projection = glm::perspective(45.0f, (float)Width / (float)Height, 0.1f, 100.0f);
    ResourceManager::GetShader("��ͨ��ɫ��").SetMatrix4("projection", projection);
}

void Game::ProcessInput(float dt)
{
    // �����������
    if (this->Keys[GLFW_KEY_W] == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (this->Keys[GLFW_KEY_S] == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (this->Keys[GLFW_KEY_A] == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (this->Keys[GLFW_KEY_D] == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);

    // �����������
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